#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H


#include <QThread>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <QtCore>

#include <QMessageBox>
#include <QTimer>
#include <vlc/vlc.h>
#include <string>
class CaptureThread : public QThread
{
    Q_OBJECT

public:
    explicit CaptureThread(int);
    explicit CaptureThread(QString,cv::Size);
    QTimer* tmrTimer;
    cv::Mat src;    
    bool stop;
    cv::Size rtspReso;
    void release_ip();
    void pause_ip();
    void release_cam();
    cv::VideoCapture capWebam;


protected:
    void run();
signals:
    void frameCaptured(cv::Mat);


public slots:
    void captureFrame();
    void captureFrame1();

private:

    cv::Mat capturedFrame;
};

#endif // CAPTURETHREAD_H
