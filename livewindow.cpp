#include "livewindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv/highgui.h>
#include <qelapsedtimer.h>
#include <iostream>
#include <libv4l2.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "QKeyEvent"
#include "qdebug.h"



#define OFFSETX 0
#define OFFSETY 0





liveWindow::liveWindow(QWidget *parent,QString PATH) :
    QLabel(parent),PATH(PATH)
{

    resize(1080,1920);
    videoPix.load(PATH+"videobg.png");
    isEnglish = true;
    QPixmap buf;
    for(int i=1;i<=5;i++)
    {
        buf.load(PATH+"AR"+QString::number(i)+".png");
        countDownARPix.push_back(buf);
        buf.load(PATH+"EN"+QString::number(i)+".png");
        countDownENPix.push_back(buf);
    }


    setPixmap(videoPix);


    videoLbl = new QLabel(this);
    videoLbl->resize(960,720);
    videoLbl->move((width()-videoLbl->width())/2,(height()-videoLbl->height())/2);
    videoLbl->show();

    countLbl = new QLabel(this);
    countLbl->resize(size());
    countLbl->move(0,0);
    //countLbl->show();


    videoThread = new QThread;
    worker = new videoWorker(NULL,PATH);
    worker->moveToThread(videoThread);
    connect(worker,SIGNAL(frameReady(QPixmap)),videoLbl,SLOT(setPixmap(QPixmap)));
    connect(videoThread, SIGNAL (started()), worker, SLOT (process()));
    connect(worker,SIGNAL(recordingOver()),this,SLOT(doneRecording()));

    videoThread->start();




}





void liveWindow::keyPressEvent( QKeyEvent *k )
{
    switch ( tolower(k->key()) ) {

    case 'q':
        exit(0);
        break;
    case 'a':
        exit(0);
        break;

    }
}







void liveWindow::startAR(QString nuvideo,bool english)
{
    videoLbl->hide();
    worker->startVideo("");//stop AR
    countDown = 4;
    isEnglish = english;
    scenario = nuvideo;
    countDownStep();

}

void liveWindow::previewVideo()
{
    QString scenar;
    qsrand(QTime::currentTime().msec());
    switch(qrand()%3)
    {
    case 0: scenar="air";break;
    case 1: scenar="water";break;
    case 2: scenar="soil";break;
    }


    videoLbl->show();
    countLbl->hide();
    worker->startVideo(scenar);
}


void liveWindow::startVideo()
{
    videoLbl->show();
    countLbl->hide();
    worker->startVideo(scenario);
    QTimer::singleShot(2000,this,SLOT(recordVideo()));
}

void liveWindow::countDownStep()
{


    countLbl->show();
    if(isEnglish)
        countLbl->setPixmap(countDownENPix.at(countDown));
    else
        countLbl->setPixmap(countDownARPix.at(countDown));

    countDown--;

    if(countDown<0)
        QTimer::singleShot(1000,this,SLOT(startVideo()));
    else
        QTimer::singleShot(1000,this,SLOT(countDownStep()));



}


void liveWindow::recordVideo()
{
    qDebug()<<"start recording";
    worker->startRecording();

}

void liveWindow::doneRecording()
{
    QString command = "ffmpeg -y -v 0 -i "+PATH+"buf.avi -r 5 -vf scale=480:-1 "+PATH+"out.gif";
    qDebug()<<"starting to process: "<<command;
    QProcess *p = new QProcess(this);
    connect(p,SIGNAL(finished(int)),this,SLOT(doneConverting()));
    p->start(command);

   // worker->startVideo("");//stop AR

}



void liveWindow::doneConverting()
{

    qDebug()<<"convertion to gif over";
    emit gifReady();
}


liveWindow::~liveWindow()
{

}
