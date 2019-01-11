#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T18:46:22
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /home/pi/
TARGET = realAugGif
INSTALLS += target

TEMPLATE = app

QT_CONFIG -= no-pkg-config
CONFIG += link_pkgconfig debug
PKGCONFIG += mpv


SOURCES += main.cpp \
    livewindow.cpp \
    interfacewindow.cpp \
    picbutton.cpp \
    videoworker.cpp \
    mpvwidget.cpp

HEADERS  += \
    livewindow.h \
    interfacewindow.h \
    picbutton.h \
    videoworker.h \
    mpvwidget.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_videoio
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect

LIBS += -lv4l2
