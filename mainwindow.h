#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startVideo();
    void stopVideo();
    void readFrame();
    void captureFrame();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture cap;
    cv::Mat currentFrame;
    QTimer *timer;
    cv::CascadeClassifier faceCascade;

};

#endif // MAINWINDOW_H
