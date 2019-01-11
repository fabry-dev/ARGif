#include "interfacewindow.h"

QStringList keyboardARStr = (QStringList)"@"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"0"<<"_"<<"-"<<"back"
                                           <<""<<"ض"<<"ص"<<"ث"<<"ق"<<"ف"<<"غ"<<"ع"<<"ه"<<"خ"<<"ح"<<"ج"<<"د"
                                          <<""<<"ش"<<"س"<<"ي"<<"ب"<<"ل"<<"ا"<<"ت"<<"ن"<<"م"<<"ك"<<"ط"
                                         <<""<<"ئ"<<"ء"<<"ؤ"<<"ر"<<"ﻻ"<<"ى"<<"ة"<<"و"<<"ز"<<"ظ"<<"."
                                        <<""<<""<<" "<<""<<""<<"enter";

QStringList keyboardENStr = (QStringList)"@"<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"<<"9"<<"0"<<"_"<<"-"<<"back"
                                           <<""<<"q"<<"w"<<"e"<<"r"<<"t"<<"y"<<"u"<<"i"<<"o"<<"p"<<""<<""
                                          <<""<<"a"<<"s"<<"d"<<"f"<<"g"<<"h"<<"j"<<"k"<<"l"<<""<<""
                                         <<""<<"z"<<"x"<<"c"<<"v"<<"b"<<"n"<<"m"<<""<<"."<<""<<""
                                        <<""<<""<<" "<<""<<""<<"enter";



interfaceWindow::interfaceWindow(QWidget *parent = 0,QString PATH=""):QLabel(parent),PATH(PATH)
{
    this->resize(1920,1080);
    english = false;
    prevScenario = "air";

    languagePix.load(PATH+"language.png");

    scenarioARPix.load(PATH+"scenarioAR.png");
    scenarioENPix.load(PATH+"scenarioEN.png");

    recordingARPix.load(PATH+"recordingAR.png");
    recordingENPix.load(PATH+"recordingEN.png");

    previewARPix.load(PATH+"previewAR.png");
    previewENPix.load(PATH+"previewEN.png");

    keyboardARPix.load(PATH+"keyboardAR.png");
    keyboardENPix.load(PATH+"keyboardEN.png");

    thanksARPix.load(PATH+"thanksAR.png");
    thanksENPix.load(PATH+"thanksEN.png");

    englishButton = new picButton(this,200,PATH+"enOFF.png",PATH+"enON.png","en");
    arabicButton = new picButton(this,200,PATH+"arOFF.png",PATH+"arON.png","ar");
    englishButton->hide();arabicButton->hide();


    connect(englishButton,SIGNAL(clicked(QString)),this,SLOT(getLanguage(QString)));
    connect(arabicButton,SIGNAL(clicked(QString)),this,SLOT(getLanguage(QString)));

    englishButton->move(830-englishButton->width()/2,650);
    arabicButton->move(1920-(830+arabicButton->width()/2),650);


    airENButton = new picButton(this,250,PATH+"airENOFF.png",PATH+"airENON.png","air");
    waterENButton = new picButton(this,250,PATH+"waterENOFF.png",PATH+"waterENON.png","water");
    soilENButton = new picButton(this,250,PATH+"soilENOFF.png",PATH+"soilENON.png","soil");

    airARButton = new picButton(this,250,PATH+"airAROFF.png",PATH+"airARON.png","air");
    waterARButton = new picButton(this,250,PATH+"waterAROFF.png",PATH+"waterARON.png","water");
    soilARButton = new picButton(this,250,PATH+"soilAROFF.png",PATH+"soilARON.png","soil");

    connect(airENButton,SIGNAL(clicked(QString)),this,SLOT(getScenario(QString)));
    connect(waterENButton,SIGNAL(clicked(QString)),this,SLOT(getScenario(QString)));
    connect(soilENButton,SIGNAL(clicked(QString)),this,SLOT(getScenario(QString)));
    connect(airARButton,SIGNAL(clicked(QString)),this,SLOT(getScenario(QString)));
    connect(waterARButton,SIGNAL(clicked(QString)),this,SLOT(getScenario(QString)));
    connect(soilARButton,SIGNAL(clicked(QString)),this,SLOT(getScenario(QString)));



    airENButton->move(670-airENButton->width()/2,650);
    soilENButton->move(1920-(670+waterENButton->width()/2),650);
    waterENButton->move((1920-waterENButton->width())/2,650);

    airARButton->move(airENButton->pos());
    waterARButton->move(waterENButton->pos());
    soilARButton->move(soilENButton->pos());


    airENButton->hide();soilENButton->hide();waterENButton->hide();
    airARButton->hide();soilARButton->hide();waterARButton->hide();

    nameEdit = new lineEdit2(this);
    connect(nameEdit,SIGNAL(clicked(lineEdit2*)),this,SLOT(selectTextZone(lineEdit2*)));
    emailEdit = new lineEdit2(this);
    connect(emailEdit,SIGNAL(clicked(lineEdit2*)),this,SLOT(selectTextZone(lineEdit2*)));
    phoneEdit = new lineEdit2(this);
    connect(phoneEdit,SIGNAL(clicked(lineEdit2*)),this,SLOT(selectTextZone(lineEdit2*)));

    nameEdit->resize(450,50);
    emailEdit->resize(nameEdit->size());
    phoneEdit->resize(nameEdit->size());

    nameEdit->move(240,470);
    emailEdit->move(736,470);
    phoneEdit->move(1231,470);

    nameEdit->hide();
    emailEdit->hide();
    phoneEdit->hide();


    gifOKENButton = new picButton(this,250,PATH+"ENOkOFF.png",PATH+"ENOkON.png","OK");
    gifNOENButton = new picButton(this,250,PATH+"ENNoOFF.png",PATH+"ENNoON.png","OK");

    gifOKENButton->move(800-gifNOENButton->width()/2,800);
    gifNOENButton->move(width()-(800+gifNOENButton->width()/2),800);

    gifOKENButton->hide();
    gifNOENButton->hide();



    gifOKARButton = new picButton(this,250,PATH+"AROkOFF.png",PATH+"AROkON.png","OK");
    gifNOARButton = new picButton(this,250,PATH+"ARNoOFF.png",PATH+"ARNoON.png","OK");

    gifOKARButton->move(800-gifNOARButton->width()/2,800);
    gifNOARButton->move(width()-(800+gifNOARButton->width()/2),800);

    gifOKARButton->hide();
    gifNOARButton->hide();


    vp = new mpvWidget(this);
    vp->resize(480,360);
    vp->move((width()-vp->width())/2,400);
    vp->setLoop(true);
    vp->hide();




    setupENKeyboard();
    setupARKeyboard();


    initDb();

    setupStates();



}







void interfaceWindow::setupENKeyboard()
{

    int kwdefault = 70;
    int kspace = 10;
    int kw;
    int ky=70+kspace;
    int posX = 0;
    int posY0 = 600;
    int posY = posY0;
    for(int i = 0;i<57;i++)
    {
        //qDebug()<<PATH+"EN/off/"+QString::number(i)+".png";
        kw = kwdefault;



        if(i==13)
            kw=2*kwdefault;
        else if((i==14))
            kw=(float)1.5*kwdefault+kspace;
        else if(i==27)
            kw=(float)2*kwdefault+kspace;
        else if(i==39)
            kw=(float)2.5*kwdefault+2*kspace;
        else if(i==50)
            kw=(float)2.5*kwdefault;
        else if(i==53)
            kw=(float)8.5*kwdefault+7*kspace;
        else if((i==51)||(i==52)||(i==54)||(i==55))
            kw=(float)1.5*kwdefault+kspace;

        else if(i==56)
        {
            kw = 2*kwdefault-kspace;
            posY = posY0+ky;
            posX-=kw;
        }



        picButton *pb = new picButton(this,kw,PATH+"EN/off/"+QString::number(i)+".png",PATH+"EN/on/"+QString::number(i)+".png",keyboardENStr[i]);
        connect(pb,SIGNAL(clicked(QString)),this,SLOT(getKey(QString)));
        pb->move(posX,posY);
        //pb->setStyleSheet("border: 1px solid black");
        posX+=kw+kspace;


        if((i==13)||(i==26)||(i==38)||(i==50))
        {
            posX=0;
            posY+=ky;
        }

        pb->show();
        keyboardEN.push_back(pb);


    }

    keyboardEN[56]->lower();


    int maxX = 0;

    for(auto p:keyboardEN)
    {
        if(p->geometry().left()>maxX)
            maxX = p->geometry().right();
    }

    for(auto p:keyboardEN)
        p->move(p->x()+(width()-maxX)/2,p->y());


    for(auto p:keyboardEN)
        p->hide();
}

void interfaceWindow::setupARKeyboard()
{

    int kwdefault = 70;
    int kspace = 10;
    int kw;
    int ky=70+kspace;
    int posX = 0;
    int posY0 = 600;
    int posY = posY0;
    for(int i = 0;i<57;i++)
    {

        kw = kwdefault;



        if(i==13)
            kw=2*kwdefault;
        else if((i==14))
            kw=(float)1.5*kwdefault+kspace;
        else if(i==27)
            kw=(float)2*kwdefault+kspace;
        else if(i==39)
            kw=(float)2.5*kwdefault+2*kspace;
        else if(i==50)
            kw=(float)2.5*kwdefault;
        else if(i==53)
            kw=(float)8.5*kwdefault+7*kspace;
        else if((i==51)||(i==52)||(i==54)||(i==55))
            kw=(float)1.5*kwdefault+kspace;

        else if(i==56)
        {
            kw = 2*kwdefault-kspace;
            posY = posY0+ky;
            posX-=kw;
        }



        picButton *pb = new picButton(this,kw,PATH+"AR/off/"+QString::number(i)+".png",PATH+"AR/on/"+QString::number(i)+".png",keyboardARStr[i]);
        connect(pb,SIGNAL(clicked(QString)),this,SLOT(getKey(QString)));
        pb->move(posX,posY);
        //pb->setStyleSheet("border: 1px solid black");
        posX+=kw+kspace;


        if((i==13)||(i==26)||(i==38)||(i==50))
        {
            posX=0;
            posY+=ky;
        }

        pb->show();
        keyboardAR.push_back(pb);


    }

    keyboardAR[56]->lower();


    int maxX = 0;

    for(auto p:keyboardAR)
    {
        if(p->geometry().left()>maxX)
            maxX = p->geometry().right();
    }

    for(auto p:keyboardAR)
        p->move(p->x()+(width()-maxX)/2,p->y());


    for(auto p:keyboardAR)
        p->hide();
}

void interfaceWindow::initDb()
{

    const QString DRIVER("QSQLITE");
    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setHostName("hostname");
    db.setDatabaseName(PATH+"ardb");
    db.setUserName("user");
    db.setPassword("password");

    if(!db.open())
        qWarning() << "ERROR: " << db.lastError();

    qDebug()<<db.tables();


    QSqlQuery query("CREATE TABLE players (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, phone TEXT, gif TEXT, date TIMESTAMP)");

    bool success = query.exec();

    if(!success)
    {
        qDebug() << query.lastError();
    }
    else qDebug() << "table created";

}

void interfaceWindow::getUsers()
{

    QSqlQuery query;
    query.prepare("SELECT id,name,email,phone,gif,date FROM players");
    query.exec();

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString email = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString gif = query.value(4).toString();
        QDateTime date = query.value(5).toDateTime();
        qDebug()<<id<<name<<email<<phone<<gif<<date;
    }
}
void interfaceWindow::insertUser(QString name, QString email, QString phone, QString gif)
{


    QDateTime timestamp = QDateTime::currentDateTime();

    QSqlQuery query;
    query.prepare("INSERT INTO players (name, email, phone,gif, date) VALUES (:name,:email,:phone,:gif,:datetime)");

    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":gif", gif);
    query.bindValue(":datetime", timestamp.toString("yyyy-MM-dd hh:mm:ss"));


    bool success = query.exec();
    if(!success)
    {
        qDebug() << query.lastError();
    }


}




void interfaceWindow::setupStates()
{
    QState *languageChoice = new QState();
    QState *scenarioChoice = new QState();
    QState *recording = new QState();
    QState *preview = new QState();
    QState *keyboard = new QState();
    QState *thanks = new QState();


    connect(languageChoice,SIGNAL(entered()),this,SLOT(goLanguageChoice()));
    connect(languageChoice,SIGNAL(entered()),this,SIGNAL(startRandomAR()));
    languageChoice->assignProperty(englishButton,"visible",true);
    languageChoice->assignProperty(arabicButton,"visible",true);



    languageChoice->assignProperty(nameEdit,"visible",false);
    languageChoice->assignProperty(emailEdit,"visible",false);
    languageChoice->assignProperty(phoneEdit,"visible",false);

    languageChoice->assignProperty(airARButton,"visible",false);
    languageChoice->assignProperty(waterARButton,"visible",false);
    languageChoice->assignProperty(soilARButton,"visible",false);
    languageChoice->assignProperty(airENButton,"visible",false);
    languageChoice->assignProperty(waterENButton,"visible",false);
    languageChoice->assignProperty(soilENButton,"visible",false);

    languageChoice->addTransition(this,SIGNAL(languageChosen()),scenarioChoice);


    connect(scenarioChoice,SIGNAL(entered()),this,SLOT(goSceneraioChoice()));
    scenarioChoice->assignProperty(englishButton,"visible",false);
    scenarioChoice->assignProperty(arabicButton,"visible",false);

    scenarioChoice->addTransition(this,SIGNAL(scenarioChosen(QString,bool)),recording);


    connect(recording,SIGNAL(entered()),this,SLOT(goRecording()));
    recording->assignProperty(airARButton,"visible",false);
    recording->assignProperty(waterARButton,"visible",false);
    recording->assignProperty(soilARButton,"visible",false);
    recording->assignProperty(airENButton,"visible",false);
    recording->assignProperty(waterENButton,"visible",false);
    recording->assignProperty(soilENButton,"visible",false);
    recording->assignProperty(vp,"visible",false);
    recording->assignProperty(gifOKENButton,"visible",false);
    recording->assignProperty(gifNOENButton,"visible",false);
    recording->assignProperty(gifOKARButton,"visible",false);
    recording->assignProperty(gifNOARButton,"visible",false);



    recording->addTransition(this,SIGNAL(gifReady()),preview);
    connect(preview,SIGNAL(entered()),this,SLOT(goPreview()));
    preview->assignProperty(vp,"visible",true);

    preview->addTransition(gifOKENButton,SIGNAL(clicked(QString)),keyboard);
    preview->addTransition(gifOKARButton,SIGNAL(clicked(QString)),keyboard);
    preview->addTransition(this,SIGNAL(scenarioChosen(QString,bool)),recording);
    connect(gifNOENButton,SIGNAL(clicked(QString)),this,SLOT(recordAgain()));
    connect(gifNOARButton,SIGNAL(clicked(QString)),this,SLOT(recordAgain()));



    connect(keyboard,SIGNAL(entered()),this,SLOT(goKeyboard()));
    keyboard->assignProperty(airARButton,"visible",false);
    keyboard->assignProperty(waterARButton,"visible",false);
    keyboard->assignProperty(soilARButton,"visible",false);
    keyboard->assignProperty(airENButton,"visible",false);
    keyboard->assignProperty(waterENButton,"visible",false);
    keyboard->assignProperty(soilENButton,"visible",false);
    keyboard->assignProperty(englishButton,"visible",false);
    keyboard->assignProperty(arabicButton,"visible",false);

    keyboard->assignProperty(nameEdit,"visible",true);
    keyboard->assignProperty(emailEdit,"visible",true);
    keyboard->assignProperty(phoneEdit,"visible",true);

    keyboard->assignProperty(vp,"visible",false);
    keyboard->assignProperty(gifOKENButton,"visible",false);
    keyboard->assignProperty(gifNOENButton,"visible",false);
    keyboard->assignProperty(gifOKARButton,"visible",false);
    keyboard->assignProperty(gifNOARButton,"visible",false);

    keyboard->addTransition(this,SIGNAL(dataValidated()),thanks);

    connect(thanks,SIGNAL(entered()),this,SLOT(goThanks()));
    thanks->addTransition(this,SIGNAL(thanksOver()),languageChoice);
    thanks->assignProperty(nameEdit,"visible",false);
    thanks->assignProperty(emailEdit,"visible",false);
    thanks->assignProperty(phoneEdit,"visible",false);




    machine.addState(languageChoice);
    machine.addState(scenarioChoice);
    machine.addState(recording);
    machine.addState(preview);
    machine.addState(keyboard);

    machine.addState(thanks);

    machine.setInitialState(languageChoice);
    machine.start();
}






void interfaceWindow::goLanguageChoice()
{
    setPixmap(languagePix);
}

void interfaceWindow::getLanguage(QString language)
{
    english = (language == "en");
    emit languageChosen();
}



void interfaceWindow::goSceneraioChoice(void)
{
    if(english)
    {
        setPixmap(scenarioENPix);
        airENButton->show();
        waterENButton->show();
        soilENButton->show();
    }
    else
    {
        setPixmap(scenarioARPix);
        airARButton->show();
        waterARButton->show();
        soilARButton->show();
    }
}





void interfaceWindow::getScenario(QString scenario)
{
   // qDebug()<<scenario;
    prevScenario = scenario;
    emit scenarioChosen(scenario,english);

}


void interfaceWindow::recordAgain()
{
    emit scenarioChosen(prevScenario,english);
}



void interfaceWindow::goRecording()
{
    if(english)
    {
        setPixmap(recordingENPix);
    }
    else
    {
        setPixmap(recordingARPix);
    }

}




void interfaceWindow::goPreview()
{

    if(english)
    {
        setPixmap(previewENPix);
        gifOKENButton->show();
        gifNOENButton->show();
    }
    else
    {
        gifOKARButton->show();
        gifNOARButton->show();
        setPixmap(previewARPix);
    }

    vp->loadFile(PATH+"out.gif");

}


void interfaceWindow::goKeyboard()
{
    if(english)
    {
        setPixmap(keyboardENPix);
        for(auto p:keyboardEN)
            p->show();

        nameEdit->setFont(QFont(PATH+"arabic.otf"));
    }
    else
    {
        setPixmap(keyboardARPix);
        for(auto p:keyboardAR)
            p->show();

        nameEdit->setFont(QFont(PATH+"english.otf"));
    }

    nameEdit->clear();
    emailEdit->clear();
    phoneEdit->clear();

    selectTextZone(nameEdit);

}


void interfaceWindow::selectTextZone(lineEdit2* ln)
{
    ln->setFocus();
    activeLine = ln;
}

void interfaceWindow::getKey(QString txt)
{
    if(txt=="enter")
    {
        if((nameEdit->text()>3)&&(emailEdit->text()>3))
        {
            validateData();
        }

    }
    else if(txt=="back")
    {
        if(activeLine->text().size()>0)
            activeLine->setText((activeLine->text()).remove((activeLine->text()).size()-1,1));

    }
    else
    {
        activeLine->setText(activeLine->text()+txt);
    }
    activeLine->setCursorPosition( activeLine->text().size());

}

void interfaceWindow::validateData()
{
    QString name,email,phone;
    name = nameEdit->text();
    email = emailEdit->text();
    phone = phoneEdit->text();

    QDateTime timestamp = QDateTime::currentDateTime();
    QString gifName =PATH+"gifs/"+timestamp.toString("yyyy-MM-dd-hh-mm-ss")+".gif";
    QString command = "cp "+PATH+"out.gif "+gifName;
    qDebug()<<command;
    system(command.toStdString().c_str());


    qDebug()<<name<<email<<phone<<gifName;

    insertUser(name,email,phone,gifName);
    getUsers();

    emit dataValidated();
}

void interfaceWindow::goThanks()
{

    for(auto p:keyboardAR)
        p->hide();
    for(auto p:keyboardEN)
        p->hide();

    if(english)
    {
        setPixmap(thanksENPix);
    }
    else
    {
        setPixmap(thanksARPix);
    }

    QTimer::singleShot(5000,this,SIGNAL(thanksOver()));
}




void interfaceWindow::mousePressEvent(QMouseEvent *ev)
{

    qDebug()<<ev->pos();
}
