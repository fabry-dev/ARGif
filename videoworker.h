#ifndef VIDEOWORKER_H
#define VIDEOWORKER_H

#include <QObject>

#include "qlabel.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>
#include "qdebug.h"

#include <qelapsedtimer.h>
#include <iostream>
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "QKeyEvent"
#include "qdebug.h"
#include "QMutex"


class videoWorker : public QObject
{
    Q_OBJECT
public:
    explicit videoWorker(QObject *parent = nullptr,QString PATH="");
    void startVideo(QString video);
    void startRecording();
    QMutex loadMutex,recMutex;
private:
    QString PATH;
    cv::VideoCapture *video,*alpha;
    cv::VideoWriter *videoOut;
    int videoFrameCount,videoFrameCount2,alphaFrameCount,alphaFrameCount2;
    int frameToRecord;

signals:
    void frameReady(QPixmap frame);
    void recordingOver();

public slots:

private slots:
    void process();

};

#endif // VIDEOWORKER_H
