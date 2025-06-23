#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QHBoxLayout>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateFrame();
    void captureFrame();
    void handleSourceSelection(int index);
    void openVideoFile();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QLabel *thumbnailLabel;
    QHBoxLayout *thumbnailLayout;

    cv::VideoCapture *capture;
    cv::Mat frame;
    cv::dnn::Net net;
    std::vector<cv::Mat> detectAndDrawFacesWithReturn(cv::Mat &frame, bool save);


    QString lastSelectedSource;
    bool isVideoPlaying;

    void setupConnections();
    void initializeDNN();
    void ensureFacesFolder();
    void showThumbnail(const cv::Mat &face);
    int detectAndDrawFaces(cv::Mat &frame, bool save);
};

#endif // MAINWINDOW_H
