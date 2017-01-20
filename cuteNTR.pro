#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T13:50:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cuteNTR
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
        ntr.cpp \
        streamworker.cpp \
        streamwindow.cpp

HEADERS  += mainwindow.h \
        ntr.h \
        streamworker.h \
        streamwindow.h

FORMS    += mainwindow.ui
