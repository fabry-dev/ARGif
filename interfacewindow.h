#ifndef INTERFACEWINDOW_H
#define INTERFACEWINDOW_H

#include <QObject>
#include "qlabel.h"
#include "qstatemachine.h"
#include "qdebug.h"
#include "picbutton.h"
#include "QLineEdit"
#include "QPushButton"
#include "qdatetime.h"
#include <QtSql>
#include <QSqlQuery>
#include "mpvwidget.h"


class lineEdit2: public QLineEdit
{
    Q_OBJECT
public:
    lineEdit2(QWidget *parent = nullptr):QLineEdit(parent)
    {installEventFilter(this);}

protected:
    /*  void focusInEvent(QFocusEvent *e)
    {

    }*/
    bool eventFilter(QObject *object, QEvent *event)
    {
        if (event->type() == QEvent::FocusIn)
        {
            emit clicked(this);
        }

        return false;
    }

signals:
    void clicked(lineEdit2*);
};








class interfaceWindow : public QLabel
{
    Q_OBJECT

public:
    interfaceWindow(QWidget *parent, QString PATH);


private:
    QString PATH;
    void setupStates();
    QStateMachine machine;
    bool english;
    QPixmap languagePix,scenarioENPix,scenarioARPix,thanksENPix,thanksARPix,recordingENPix,recordingARPix,previewARPix,previewENPix,keyboardARPix,keyboardENPix;
    picButton *englishButton,*arabicButton;
    picButton *airARButton,*waterARButton,*soilARButton;
    picButton *airENButton,*waterENButton,*soilENButton;

    picButton *gifOKENButton,*gifNOENButton,*gifOKARButton,*gifNOARButton;


    std::vector<picButton*> keyboardEN,keyboardAR;

    lineEdit2 *nameEdit,*emailEdit,*phoneEdit,*activeLine;

    mpvWidget *vp;

    void setupENKeyboard(void);
    void setupARKeyboard(void);
    void initDb();
    void getUsers();
    void insertUser(QString name, QString email, QString phone, QString gif);
    void validateData();

    QString prevScenario;



private slots:
    void goLanguageChoice(void);
    void goSceneraioChoice(void);
    void goRecording();
    void goPreview();
    void goKeyboard();
    void goThanks();
    void getLanguage(QString);
    void getScenario(QString);
    void recordAgain();
    void getKey(QString);

    void selectTextZone(lineEdit2* ln);

signals:
    void languageChosen();
    void scenarioChosen(QString,bool);
    void recordVideo();
    void dataValidated();
    void thanksOver();
    void gifReady();
    void startRandomAR();//Only AR no recording

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // INTERFACEWINDOW_H
