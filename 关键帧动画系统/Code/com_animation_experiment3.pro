#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T19:59:03
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = com_animation_experiment1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainscene.cpp \
    my_qgraphicsview.cpp

HEADERS  += mainwindow.h \
    mainscene.h \
    my_qgraphicsview.h

FORMS    += mainwindow.ui

RESOURCES += \
    pic.qrc

DISTFILES += \
    myRc.rc \
    pic/button1.png \
    pic/button2.png \
    pic/button3.png

RC_FILE = \
    myRc.rc
