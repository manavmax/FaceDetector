#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDateTime>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), capture(nullptr) {
    ui->setupUi(this);

    thumbnailLayout = qobject_cast<QHBoxLayout*>(ui->thumbnailContainer);

    timer = new QTimer(this);
    setupConnections();
    initializeDNN();
    ensureFacesFolder();

    // Premium UI Styling
    this->setStyleSheet("QMainWindow { background-color: #1e1e2f; }");

    QString buttonStyle =
        "QPushButton {"
        "   background-color: #4CAF50;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 10px;"
        "   padding: 8px 16px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #45a049;"
        "}";

    ui->captureButton->setStyleSheet(buttonStyle);
    ui->startButton->setStyleSheet(buttonStyle);
    ui->stopButton->setStyleSheet(buttonStyle);

    ui->videoLabel->setStyleSheet("QLabel { border: 2px solid #4CAF50; background-color: #2e2e3e; }");
    ui->faceCountLabel->setStyleSheet("QLabel { color: #00FF7F; font-weight: bold; font-size: 16px; }");
    ui->statusLabel->setStyleSheet("QLabel { color: #CCCCFF; font-size: 14px; }");
    ui->sourceComboBox->setStyleSheet(
        "QComboBox {"
        "   background-color: #3b3b4f;"
        "   color: white;"
        "   padding: 4px 8px;"
        "   border-radius: 6px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background-color: #2e2e3e;"
        "   color: white;"
        "}");

    ui->thumbnailFrame->setStyleSheet("background-color: #2e2e3e; border: 1px solid #444;");
}

MainWindow::~MainWindow() {
    delete timer;
    if (capture && capture->isOpened()) {
        capture->release();
    }
    delete capture;
    delete ui;
}

void MainWindow::setupConnections() {
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    connect(ui->captureButton, &QPushButton::clicked, this, &MainWindow::captureFrame);

    // Track last index to prevent unnecessary reloads
    static int lastIndex = -1;
    connect(ui->sourceComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [=](int index) mutable {
        if (index == lastIndex) return;
        lastIndex = index;
        handleSourceSelection(index);
    });

    connect(ui->startButton, &QPushButton::clicked, this, [=]() {
        int index = ui->sourceComboBox->currentIndex();
        if (index == 1) {
            handleSourceSelection(1);
        } else if (index == 2) {
            handleSourceSelection(2);
        } else {
            QMessageBox::information(this, "Info", "Please select a valid source.");
        }
    });

    connect(ui->stopButton, &QPushButton::clicked, this, [=]() {
        timer->stop();
        if (capture) capture->release();
        ui->statusLabel->setText("✨Status : Stopped");
    });
}

void MainWindow::handleSourceSelection(int index) {
    if (capture && capture->isOpened()) {
        capture->release();
        delete capture;
        capture = nullptr;
    }

    switch (index) {
    case 1: { // Webcam
        capture = new cv::VideoCapture(0);
        if (!capture->isOpened()) {
            QMessageBox::warning(this, "Error", "Cannot open webcam");
            return;
        }
        timer->start(30);
        ui->statusLabel->setText("🎥 Webcam Streaming...");
        break;
    }
    case 2: { // Browse File
        QString filePath = QFileDialog::getOpenFileName(this, "Open Video File", "", "Videos (*.mp4 *.avi *.mov)");
        if (filePath.isEmpty()) return;

        capture = new cv::VideoCapture(filePath.toStdString());
        if (!capture->isOpened()) {
            QMessageBox::warning(this, "Error", "Cannot open selected video");
            return;
        }
        timer->start(30);
        ui->statusLabel->setText("📂 Playing from File...");
        break;
    }
    default:
        ui->statusLabel->setText("✨Status : Idle");
        break;
    }
}

void MainWindow::initializeDNN() {
    QString modelPath = QCoreApplication::applicationDirPath();
    QString proto = modelPath + "/deploy.prototxt";
    QString model = modelPath + "/res10_300x300_ssd_iter_140000.caffemodel";

    try {
        net = cv::dnn::readNetFromCaffe(proto.toStdString(), model.toStdString());
    } catch (const cv::Exception &e) {
        QMessageBox::critical(this, "DNN Load Error", e.what());
        exit(-1);
    }
}

void MainWindow::ensureFacesFolder() {
    QDir facesDir(QCoreApplication::applicationDirPath() + "/faces");
    if (!facesDir.exists()) facesDir.mkpath(".");
}

void MainWindow::updateFrame() {
    if (!capture || !capture->isOpened()) return;

    *capture >> frame;
    if (frame.empty()) return;

    int facesDetected = detectAndDrawFaces(frame, false);

    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_BGR888);
    ui->videoLabel->setPixmap(QPixmap::fromImage(qimg).scaled(ui->videoLabel->size(), Qt::KeepAspectRatio));
    ui->faceCountLabel->setText(QString("😃 Faces Detected: %1").arg(facesDetected));
}

void MainWindow::captureFrame() {
    if (frame.empty()) return;

    std::vector<cv::Mat> faces = detectAndDrawFacesWithReturn(frame, true);

    for (const auto &face : faces) {
        showThumbnail(face);
    }

    if (!faces.empty()) {
        QMessageBox::information(this, "Capture", QString("Captured %1 face(s).").arg(faces.size()));
    } else {
        QMessageBox::information(this, "Capture", "No face detected.");
    }
}

void MainWindow::showThumbnail(const cv::Mat &face) {
    if (face.empty() || !thumbnailLayout) return;

    cv::Mat rgb;
    cv::cvtColor(face, rgb, cv::COLOR_BGR2RGB);
    QImage qimg(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);

    QLabel *label = new QLabel(this);
    label->setPixmap(QPixmap::fromImage(qimg).scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    label->setFixedSize(70, 70);
    label->setStyleSheet("border: 1px solid #ccc; margin: 2px;");

    thumbnailLayout->addWidget(label);
}

int MainWindow::detectAndDrawFaces(cv::Mat &frame, bool save) {
    int w = frame.cols, h = frame.rows;
    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300),
                                          cv::Scalar(104.0, 177.0, 123.0), false, false);
    net.setInput(blob);
    cv::Mat detections = net.forward();

    int facesDetected = 0;
    for (int i = 0; i < detections.size[2]; ++i) {
        float confidence = detections.ptr<float>(0, 0)[i * 7 + 2];
        if (confidence > 0.6) {
            int x1 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 3] * w);
            int y1 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 4] * h);
            int x2 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 5] * w);
            int y2 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 6] * h);

            cv::Rect faceRect(x1, y1, x2 - x1, y2 - y1);
            cv::rectangle(frame, faceRect, cv::Scalar(0, 255, 0), 2);

            if (save) {
                cv::Mat face = frame(faceRect).clone();
                QString filename = QCoreApplication::applicationDirPath() + "/faces/face_" +
                                   QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz") + ".png";
                cv::imwrite(filename.toStdString(), face);
            }

            ++facesDetected;
        }
    }

    return facesDetected;
}

std::vector<cv::Mat> MainWindow::detectAndDrawFacesWithReturn(cv::Mat &frame, bool save) {
    std::vector<cv::Mat> savedFaces;
    int w = frame.cols, h = frame.rows;

    cv::Mat blob = cv::dnn::blobFromImage(frame, 1.0, cv::Size(300, 300),
                                          cv::Scalar(104.0, 177.0, 123.0), false, false);
    net.setInput(blob);
    cv::Mat detections = net.forward();

    for (int i = 0; i < detections.size[2]; ++i) {
        float confidence = detections.ptr<float>(0, 0)[i * 7 + 2];
        if (confidence > 0.6) {
            int x1 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 3] * w);
            int y1 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 4] * h);
            int x2 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 5] * w);
            int y2 = static_cast<int>(detections.ptr<float>(0, 0)[i * 7 + 6] * h);

            cv::Rect faceRect(x1, y1, x2 - x1, y2 - y1);
            cv::rectangle(frame, faceRect, cv::Scalar(0, 255, 0), 2);

            if (save) {
                cv::Mat face = frame(faceRect).clone();
                QString filename = QCoreApplication::applicationDirPath() + "/faces/face_" +
                                   QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss_zzz") + ".png";
                cv::imwrite(filename.toStdString(), face);
                savedFaces.push_back(face);
            }
        }
    }

    return savedFaces;
}

void MainWindow::openVideoFile() {
    QString filePath = QFileDialog::getOpenFileName(this, "Open Video File", "", "Videos (*.mp4 *.avi *.mov)");
    if (filePath.isEmpty()) return;

    if (capture) {
        capture->release();
        delete capture;
    }
    capture = new cv::VideoCapture(filePath.toStdString());
    if (!capture->isOpened()) {
        QMessageBox::warning(this, "Error", "Cannot open video file");
        return;
    }

    timer->start(30);
    ui->statusLabel->setText("📂 Playing from File...");
}
