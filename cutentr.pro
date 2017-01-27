#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T13:50:44
#
#-------------------------------------------------

TARGET = cutentr
TEMPLATE = subdirs
SUBDIRS += src
VERSION = -0.1.1

isEmpty(PREFIX): PREFIX = /usr/local

desktop.files = setup/gui/cutentr.desktop
desktop.path = $$PREFIX/share/applications

INSTALLS += desktop

DISTFILES += $$desktop.files
