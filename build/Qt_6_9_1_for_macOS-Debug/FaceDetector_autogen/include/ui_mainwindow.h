/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *statusLabel;
    QComboBox *sourceComboBox;
    QLabel *videoLabel;
    QLabel *faceCountLabel;
    QWidget *thumbnailFrame;
    QHBoxLayout *thumbnailContainer;
    QPushButton *captureButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(798, 750);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        statusLabel->setFont(font);
        statusLabel->setStyleSheet(QString::fromUtf8("color: violet;"));

        verticalLayout->addWidget(statusLabel);

        sourceComboBox = new QComboBox(centralwidget);
        sourceComboBox->addItem(QString());
        sourceComboBox->addItem(QString());
        sourceComboBox->addItem(QString());
        sourceComboBox->setObjectName("sourceComboBox");

        verticalLayout->addWidget(sourceComboBox);

        videoLabel = new QLabel(centralwidget);
        videoLabel->setObjectName("videoLabel");
        videoLabel->setMinimumSize(QSize(640, 480));
        videoLabel->setFrameShape(QFrame::Shape::Box);
        videoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(videoLabel);

        faceCountLabel = new QLabel(centralwidget);
        faceCountLabel->setObjectName("faceCountLabel");
        QFont font1;
        font1.setBold(true);
        faceCountLabel->setFont(font1);
        faceCountLabel->setStyleSheet(QString::fromUtf8("color: green;"));

        verticalLayout->addWidget(faceCountLabel);

        thumbnailFrame = new QWidget(centralwidget);
        thumbnailFrame->setObjectName("thumbnailFrame");

        verticalLayout->addWidget(thumbnailFrame);

        thumbnailContainer = new QHBoxLayout();
        thumbnailContainer->setObjectName("thumbnailContainer");

        verticalLayout->addLayout(thumbnailContainer);

        captureButton = new QPushButton(centralwidget);
        captureButton->setObjectName("captureButton");

        verticalLayout->addWidget(captureButton);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");

        verticalLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");

        verticalLayout->addWidget(stopButton);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Face Detector", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "\342\234\250Status : Idle", nullptr));
        sourceComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Select Source", nullptr));
        sourceComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "WebCam", nullptr));
        sourceComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "LocalFiles", nullptr));

        faceCountLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\230\203 Faces Detected: 0", nullptr));
        captureButton->setText(QCoreApplication::translate("MainWindow", "\360\237\223\270 Capture", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\360\237\237\242 Start", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\360\237\224\264 Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
