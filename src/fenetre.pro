# -------------------------------------------------
# Project created by QtCreator 2012-12-10T12:56:30
# -------------------------------------------------
QT += opengl xml
TARGET = fenetre
TEMPLATE = app

SOURCES += main.cpp \
    View/mainwindow.cpp \
    View/GLWidget.cpp \
    Controler/Visualization.cpp \
    Model/scene.cpp \
    Model/step.cpp \
    Model/fakesimu.cpp

HEADERS += Controler/Visualization.hpp \
    View/mainwindow.hpp \
    View/GLWidget.hpp \
    Model/scene.h \
    Model/step.h \
    Model/fakesimu.h

FORMS += View/mainwindow.ui
CONFIG += opengl
