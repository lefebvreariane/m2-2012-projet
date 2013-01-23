# -------------------------------------------------
# Project created by QtCreator 2012-12-10T12:56:30
# -------------------------------------------------
QT += opengl
TARGET = fenetre
TEMPLATE = app

SOURCES += main.cpp \
    View/mainwindow.cpp \
    Controler/Visualization.cpp

HEADERS += Controler/Visualization.h \
    View/mainwindow.h

FORMS += View/mainwindow.ui

CONFIG += opengl
