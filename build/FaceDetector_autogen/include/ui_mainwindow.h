/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *faceCountLabel;
    QComboBox *sourceComboBox;
    QLabel *videoLabel;
    QPushButton *captureButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(798, 687);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        faceCountLabel = new QLabel(centralwidget);
        faceCountLabel->setObjectName("faceCountLabel");

        verticalLayout->addWidget(faceCountLabel);

        sourceComboBox = new QComboBox(centralwidget);
        sourceComboBox->addItem(QString());
        sourceComboBox->addItem(QString());
        sourceComboBox->setObjectName("sourceComboBox");

        verticalLayout->addWidget(sourceComboBox);

        videoLabel = new QLabel(centralwidget);
        videoLabel->setObjectName("videoLabel");
        videoLabel->setMinimumSize(QSize(640, 480));
        videoLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(videoLabel);

        captureButton = new QPushButton(centralwidget);
        captureButton->setObjectName("captureButton");

        verticalLayout->addWidget(captureButton);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");

        verticalLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");

        verticalLayout->addWidget(stopButton);


        verticalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        faceCountLabel->setText(QCoreApplication::translate("MainWindow", "Face: 0", nullptr));
        sourceComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "WebCam", nullptr));
        sourceComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Local Files", nullptr));

        videoLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        captureButton->setText(QCoreApplication::translate("MainWindow", "Capture", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
