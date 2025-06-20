#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::readFrame);

    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startVideo);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopVideo);
    connect(ui->captureButton, &QPushButton::clicked, this, &MainWindow::captureFrame);

    ui->sourceComboBox->addItem("Webcam");
    ui->sourceComboBox->addItem("Local File");

    // Make sure faces folder exists
    QDir().mkpath("faces");

    // Load Haar Cascade
    QString xmlPath = QCoreApplication::applicationDirPath() + "/haarcascade_frontalface_default.xml";
    qDebug() << "Loading Haar cascade from:" << xmlPath;

    if (!faceCascade.load(xmlPath.toStdString())) {
        QMessageBox::critical(this, "Error", "Failed to load Haar cascade from:\n" + xmlPath);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::startVideo() {
    QString source = ui->sourceComboBox->currentText();

    if (source == "Webcam") {
        cap.open(0);  // Use OpenCV default webcam
    } else {
        QString filename = QFileDialog::getOpenFileName(this, "Select Video File",
                                                        QDir::homePath(),
                                                        "Videos (*.mp4 *.avi *.mov *.mkv);;All Files (*)");
        if (filename.isEmpty()) return;

        qDebug() << "Opening file:" << filename;
        cap.open(filename.toStdString());  // Use OpenCV backend directly
    }

    if (!cap.isOpened()) {
        QMessageBox::critical(this, "Error", "Failed to open video source.");
        return;
    }

    timer->start(30); // ~30 FPS
}

void MainWindow::stopVideo() {
    timer->stop();
    cap.release();
    ui->videoLabel->clear();
    ui->faceCountLabel->setText("Faces: 0");
}

void MainWindow::readFrame() {
    cap.read(currentFrame);
    if (currentFrame.empty()) return;

    std::vector<cv::Rect> faces;
    cv::Mat gray;
    cv::cvtColor(currentFrame, gray, cv::COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, faces);

    for (const auto& face : faces) {
        cv::rectangle(currentFrame, face, cv::Scalar(0, 255, 0), 2);
    }

    ui->faceCountLabel->setText(QString("Faces: %1").arg(faces.size()));

    cv::Mat rgb;
    cv::cvtColor(currentFrame, rgb, cv::COLOR_BGR2RGB);
    QImage img(rgb.data, rgb.cols, rgb.rows, rgb.step, QImage::Format_RGB888);
    ui->videoLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->videoLabel->size(), Qt::KeepAspectRatio));
}

void MainWindow::captureFrame() {
    if (currentFrame.empty()) {
        QMessageBox::warning(this, "Warning", "No video frame to capture.");
        return;
    }

    std::vector<cv::Rect> faces;
    cv::Mat gray;
    cv::cvtColor(currentFrame, gray, cv::COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, faces);

    int count = 0;
    for (const auto& face : faces) {
        cv::Mat faceROI = currentFrame(face);
        QString filename = QString("faces/face_%1.png").arg(QDateTime::currentSecsSinceEpoch() + count++);
        cv::imwrite(filename.toStdString(), faceROI);
    }

    QMessageBox::information(this, "Capture", QString("Saved %1 face(s).").arg(count));
}
