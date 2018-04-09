#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T19:59:03
#
#-------------------------------------------------
QT       += multimedia
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = com_animation_experiment1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    line.cpp \
    mainscene.cpp \
    my_qgraphicsview.cpp \
    info.cpp \
    points.cpp

HEADERS  += mainwindow.h \
    mainscene.h \
    line.h \
    my_qgraphicsview.h \
    info.h \
    points.h

FORMS    += mainwindow.ui

RESOURCES += \
    pic.qrc

DISTFILES += \
    myRc.rc \
    pic/button2.png \
    pic/button3.png

RC_FILE = \
    myRc.rc
