#-------------------------------------------------
#
# Project created by QtCreator 2012-12-10T12:56:30
#
#-------------------------------------------------

QT       += opengl core xml

TARGET = fenetre
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sceneparser.cpp

HEADERS  += mainwindow.h \
    sceneparser.h

FORMS    += mainwindow.ui

CONFIG   += opengl
