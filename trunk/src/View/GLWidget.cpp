#include <QtGui>
#include <math.h>
#include <iostream>
#include "GLWidget.hpp"
#include <cmath>
#include <QImage>
#include <QTimer>

using namespace std;

GLWidget::GLWidget(float _span, unsigned int _nbStep, Scene _scene, QWidget *parent):
    QGLWidget(parent),
    scene(_scene),
    step(0),
    nbStep(_nbStep),
    span(_span),
    yInit(30){
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    resizeGL(500,500);
    timer->start(span*1000);
    //connect(*scene,SIGNAL(valueChanged()),this,SLOT(updateGL()));
}

GLWidget::~GLWidget(){
    timer->stop();
    delete timer;
}

void GLWidget::updateTime(){
    step += 1;
    if (step < nbStep)
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
//    glEnable(GL_LIGHTING);
//
//    glEnable(GL_LIGHT0);
//    float pos[] = {0, 0, 0, 1};
//    float ambient[] = {0.25, 0.25, 0.25, 1};
//    float diffuse[] = {0.75, 0.75, 0.75, 1};
//    glLightfv(GL_LIGHT0, GL_POSITION, pos);
//    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
       GLfloat ambientLight[]={0.1,0.1,0.1,1.0};    	             // set ambient light parameters
       GLfloat diffuseLight[]={0.8,0.8,0.8,1.0};    	             // set diffuse light parameters
       GLfloat specularLight[]={0.5,0.5,0.5,1.0};  	               // set specular light parameters
       glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
       glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
       glLightfv(GL_LIGHT0,GL_SPECULAR,specularLight);

       GLfloat lightPos[]={0.0,30.0,60.0,0.0};      	              // set light position
       glLightfv(GL_LIGHT0,GL_POSITION,lightPos);

       GLfloat specularReflection[]={1.0,1.0,1.0,1.0};  	          // set specularity
       glMaterialfv(GL_FRONT, GL_SPECULAR, specularReflection);
       glMateriali(GL_FRONT,GL_SHININESS,128);

       glEnable(GL_LIGHT0);                         	              // activate light0
       glEnable(GL_LIGHTING);                       	              // enable lighting
       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); 	     // set light model
       glEnable(GL_COLOR_MATERIAL);                 	              // activate material
       glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
       glEnable(GL_NORMALIZE);                      	              // normalize normal vectors

}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //Affichage des objets
    afficherScene();
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
    gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 700.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLWidget::afficherScene(){
    glPushMatrix();
    // Affichage de la position des Objets
    // --------------------
        glTranslatef(0,yInit-step*span*5,-600);
        glPointSize(5.0);
        GLfloat *point = new GLfloat[3];
        glColor3f(255,0,0);
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


