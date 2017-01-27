#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T13:50:44
#
#-------------------------------------------------

QT       += core gui network widgets
CONFIG   += c++11

TARGET = cutentr
TEMPLATE = app
VERSION = -0.1.1

BUILD_DIR = $$shadowed($$PWD)
isEmpty(PREFIX): PREFIX = /usr/local
target.path = $$PREFIX/bin

desktop.files = setup/gui/cutentr.desktop
desktop.path = $$PREFIX/share/applications

INSTALLS += target desktop

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

DISTFILES += cutentr.desktop
