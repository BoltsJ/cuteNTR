#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T13:50:44
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = cutentr
TEMPLATE = app
VERSION = -0.0.0

BUILD_DIR = $$shadowed($$PWD)
isEmpty(PREFIX): PREFIX = /usr/local
target.path = $$PREFIX/bin
INSTALLS += target

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
