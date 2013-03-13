#include <QtGui>
#include <math.h>
#include <iostream>
#include "GLWidget.hpp"
#include <cmath>
#include <QImage>
#include <QTimer>

using namespace std;

GLWidget::GLWidget(Scene _scene, QWidget *parent):
        QGLWidget(parent), scene(_scene), Time(0)  {
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(100);
    //connect(*scene,SIGNAL(valueChanged()),this,SLOT(updateGL()));
}

GLWidget::~GLWidget(){
    timer->stop();
    delete timer;
}

void GLWidget::updateTime(){
    Time += 0.1;
    updateGL();
}

void GLWidget::initializeGL()
{
    // GL init //
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // lumiere
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    float pos[] = {0, 0, 0, 1};
    float ambient[] = {0.25, 0.25, 0.25, 1};
    float diffuse[] = {0.75, 0.75, 0.75, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Affichage des objets
    afficherCourbe();
}

void GLWidget::paintEvent(QPaintEvent *event){
    QGLWidget::paintEvent(event);
}


void GLWidget::resizeGL(int width, int height){
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 600.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::afficherCourbe(){
    glPushMatrix();
    // Affichage de la position des Objets
    // --------------------
        glTranslatef(0,0,-500);
        glPointSize(5.0);
        GLfloat *point = new GLfloat[3];
        glBegin(GL_POINTS);
            point[0] = -200;
            point[1] = 0;
            point[2] = 0;
            glVertex3fv(point);
            point[0] = 200;
            point[1] = 0;
            point[2] = 0;
            glVertex3fv(point);
        glEnd();

        glBegin(GL_LINES);
            point[0] = -200;
            point[1] = 0;
            point[2] = 0;
            glVertex3fv(point);
            point[0] = 200;
            point[1] = 0;
            point[2] = 0;
            glVertex3fv(point);
        glEnd();
        delete [] point;
    glPopMatrix();
}


