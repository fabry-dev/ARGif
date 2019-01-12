#include "videoworker.h"


using namespace cv;
using namespace std;



videoWorker::videoWorker(QObject *parent,QString PATH) : QObject(parent),PATH(PATH)
{

    video = new VideoCapture();
    alpha = new VideoCapture();

    video->release();
    alpha->release();

    videoFrameCount = 0;
    videoFrameCount2 = 0;
    alphaFrameCount = 0;
    alphaFrameCount2 = 0;

    videoOut = new VideoWriter();
    videoOut->release();

    loadMutex.unlock();
    recMutex.unlock();



    //VideoWriter videoOut(,CV_FOURCC('M','J','P','G'),10, Size(960,720));






}










void videoWorker::process()
{


    VideoCapture stream(0);

    QString videoName = PATH+"water.mp4";
    QString alphaName = PATH+"waterA.mp4";
    QString outVideoName = PATH+"buf.avi";





    Mat frame,videoFrame,alphaFrame;

    stream.set(CV_CAP_PROP_FOURCC,CV_FOURCC('M','J','P','G'));
    stream.set(CV_CAP_PROP_FRAME_WIDTH,960);
    stream.set(CV_CAP_PROP_FRAME_HEIGHT,720);





    int nFPS =stream.get(CV_CAP_PROP_FPS);
    qDebug()  << "Loaded FPS : " << nFPS << "\n";


    if (!stream.isOpened()) { //check if video device has been initialised
        cout << "cannot open camera";}



    //unconditional loop


    while (true) {



        stream >> frame;



        cv::flip(frame, frame, 1);


        loadMutex.lock();
        if((video->isOpened())&&(alpha->isOpened()))
        {


            (*video) >> videoFrame;
            (*alpha) >> alphaFrame;


            videoFrameCount2 = video->get(CV_CAP_PROP_POS_FRAMES);
            alphaFrameCount2 = alpha->get(CV_CAP_PROP_POS_FRAMES);


            if((videoFrameCount2==videoFrameCount)||(alphaFrameCount2==alphaFrameCount))
            {


                video->set(CV_CAP_PROP_POS_FRAMES,0);
                alpha->set(CV_CAP_PROP_POS_FRAMES,0);
                (*video) >> videoFrame;
                (*alpha) >> alphaFrame;
                videoFrameCount2 = video->get(CV_CAP_PROP_POS_FRAMES);
                alphaFrameCount2 = alpha->get(CV_CAP_PROP_POS_FRAMES);
                //   break;

            }
            videoFrameCount = videoFrameCount2;
            alphaFrameCount = alphaFrameCount2;


            //  cv::resize(videoFrame,videoFrame,Size(),0.5,0.5);
            //  cv::resize(alphaFrame,alphaFrame,Size(),0.5,0.5);




            float a;
            for(int x=0;x< alphaFrame.cols;x++)
                for(int y=0;y< alphaFrame.rows;y++)
                {


                    a = (float)alphaFrame.at<Vec3b>(Point(x,y))[0]/255;

                    if(a>0)
                    {
                        //  qDebug()<<x<<y;
                        if((x<frame.cols)&&(y<frame.rows)&&(x<videoFrame.cols)&&(y<videoFrame.rows))
                            //qDebug()<<videoFrame.at<Vec3b>(Point(x,y))[0];
                            frame.at<Vec3b>(Point(x,y)) = frame.at<Vec3b>(Point(x,y))*(1-a)+ a*videoFrame.at<Vec3b>(Point(x,y));
                    }
                }

        }
        loadMutex.unlock();



        recMutex.lock();
        if(videoOut->isOpened())
        {
            if(frameToRecord>0)
            {
                videoOut->write(frame);
                frameToRecord--;
            }
            else
            {
                videoOut->release();
                emit recordingOver();
            }

        }
        recMutex.unlock();



        cvtColor(frame,frame, CV_BGR2RGB);
        emit frameReady(QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888)));


    }

    stream.release();
    video->release();
    alpha->release();
    videoOut->release();
}



void videoWorker::startVideo(QString nuvideo)
{

    loadMutex.lock();
    if(nuvideo == "")
    {
        video->release();
        alpha->release();

        qDebug()<<"video stopped";
    }
    else
    {

        QString videoName = PATH+nuvideo+".mp4";
        QString alphaName = PATH+nuvideo+"A.mp4";

        video->open(videoName.toStdString().c_str());
        alpha->open(alphaName.toStdString().c_str());
        videoFrameCount = 0;
        videoFrameCount2 = 0;
        alphaFrameCount = 0;
        alphaFrameCount2 = 0;

        qDebug()<<"load "<<videoName<<alphaName;

    }
    loadMutex.unlock();
}



void videoWorker::startRecording()
{
    recMutex.lock();
    QString outVideoName = PATH+"buf.avi";
    frameToRecord = 90;
    videoOut->open(outVideoName.toStdString().c_str(),CV_FOURCC('M','J','P','G'),30, Size(960,720),true);
    recMutex.unlock();
}
