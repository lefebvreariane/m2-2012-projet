# -------------------------------------------------
# Project created by QtCreator 2012-12-10T12:56:30
# -------------------------------------------------
QT += opengl xml
TARGET = fenetre
TEMPLATE = app

SOURCES += main.cpp \
    View/mainwindow.cpp \
    Controler/Visualization.cpp \
    Model/xmlscene.cpp \
    Model/realscene.cpp

HEADERS += Controler/Visualization.h \
    View/mainwindow.h \
    Model/xmlscene.h \
    Model/realscene.h

FORMS += View/mainwindow.ui

#CONFIG += opengl xml
