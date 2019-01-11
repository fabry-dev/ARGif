#include "livewindow.h"
#include "interfacewindow.h"
#include <QApplication>
#include "qfile.h"
#include "qdebug.h"
#include "qscreen.h"


#define PATH_DEFAULT "/home/fred/Dropbox/Taf/Cassiopee/realAugGif/files/"






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QString PATH;
    QStringList params = a.arguments();

    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;



    bool HIDE_CURSOR=false;

    QFile file(PATH+"config.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no config file";

    }
    else
    {

        QTextStream in(&file);

        QString  line;
        QString paramName,paramValue;
        QStringList params;

        while(!in.atEnd()) {
            line = in.readLine();
            line = (line.split("#"))[0];
            params = line.split("=");
            if(params.size()>=2)
            {
                paramName = params[0];
                paramValue = params[1];

                if (paramName.mid(0,6)=="CURSOR")
                    HIDE_CURSOR = (paramValue=="NO");
                else
                    qDebug()<<paramName<<" - "<<paramValue;
            }
        }
        file.close();

    }



    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        a.setOverrideCursor(cursor);
        a.changeOverrideCursor(cursor);
    }


    qDebug()<<"screen count "<<a.screens().size();


    interfaceWindow *iw = new interfaceWindow(NULL,PATH);


    QScreen* screen1 = a.screens().at(1);
    QScreen* screen2 = a.screens().at(2);

    iw->setGeometry(screen1->geometry().x(),screen1->geometry().y(),1920,1080);

    liveWindow *lw = new liveWindow(NULL);
    lw->setGeometry(screen2->geometry().x(),screen2->geometry().y(),1080,1920);
    lw->showFullScreen();

    iw->showFullScreen();

    a.connect(iw,SIGNAL(scenarioChosen(QString,bool)),lw,SLOT(startAR(QString,bool)));
    a.connect(iw,SIGNAL(recordVideo()),lw,SLOT(recordVideo()));
    a.connect(lw,SIGNAL(gifReady()),iw,SIGNAL(gifReady()));
    a.connect(iw,SIGNAL(startRandomAR()),lw,SLOT(previewVideo()));
    return a.exec();
}
