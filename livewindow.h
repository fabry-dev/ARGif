#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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
#include "videoworker.h"
#include "qthread.h"
#include "QProcess"
#include "QTimer"
#include "QTime"


namespace Ui {
class MainWindow;
}

class liveWindow : public QLabel
{
    Q_OBJECT

public:
    explicit liveWindow(QWidget *parent = 0, QString PATH="");
    ~liveWindow();

protected:
void keyPressEvent( QKeyEvent *k );

private:
    QString PATH;
    int imgDistance(cv::Vec3b src);
    QLabel *videoLbl,*countLbl;
    QPixmap videoPix;
    QThread *videoThread;
    videoWorker *worker;
    int countDown;
    std::vector<QPixmap> countDownENPix,countDownARPix;
    bool isEnglish;
    QString scenario;

private slots:
    void startAR(QString, bool english);
    void recordVideo();
    void doneRecording();
    void doneConverting();
    void countDownStep();
    void startVideo();
    void previewVideo();

signals:
    void gifReady();
};

#endif // MAINWINDOW_H
