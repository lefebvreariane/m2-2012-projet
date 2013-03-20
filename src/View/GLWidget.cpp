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
    span(_span){

    // bounding box
    pair<pair<float,float> ,pair<float,float> > boundingBox = scene.min_max();
    pMin = boundingBox.first;
    pMax = boundingBox.second;

    resizeGL(500,500);
    // interactions souris
    zoomFactor = 1;
    transX = transY = 0;
    state = MOUSE_UP;

    // start timer
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    timer->start(span*1000);
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
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // projection ortho
    float w = (float) width()/zoomFactor;
    float h = (float) height()/zoomFactor;

    float l,r,b,t;
    l = -w/2.f;
    r = w/2.f;
    b = -h/2.f;
    t = h/2.f;
    glOrtho(l,r,b,t,-1,1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // translation
    glTranslatef(transX/zoomFactor, -transY/zoomFactor, 0);


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
}

void GLWidget::afficherScene(){

    glPushMatrix();
    GLfloat *point = new GLfloat[2];
    // hold die
    glColor3f(255,0,0);
    glBegin(GL_POLYGON);
    for (unsigned int i=0 ; i<scene.matrix().size() ; i++){
        point[0] = scene.matrix()[i].first;
        point[1] = scene.matrix()[i].second;
        glVertex2fv(point);
    }
    glEnd();

    // strippers
    glColor3f(100,100,100);
    for (unsigned int i=0 ; i<scene.strippers().size() ; i++){
        glBegin(GL_POLYGON);
        for (unsigned int j=0 ; j<scene.strippers()[i].second.size() ; j++){
            point[0] = scene.strippers()[i].second[j].first;
            point[1] = scene.strippers()[i].second[j].second;
            glVertex2fv(point);
        }
        glEnd();
    }

    // punch
    glColor3f(0,0,255);
    glBegin(GL_POLYGON);
    for (unsigned int i=0 ; i<scene.punch().first.size() ; i++){
        point[0] = scene.punch().first[i].first;
        point[1] = scene.punch().first[i].second;
        glVertex2fv(point);
    }
    glEnd();

    // metal strip
    glColor3f(0,255,0);
    glBegin(GL_POLYGON);
    for (unsigned int i=0 ; i<scene.sheet().second.size() ; i++){
        point[0] = scene.sheet().second[i].first;
        point[1] = scene.sheet().second[i].second;
        glVertex2fv(point);
    }
    glEnd();
    glPopMatrix();
}

void GLWidget::wheelEvent(QWheelEvent *event){
    if (event->delta() > 0)
        zoomFactor += 0.1;
    else if(zoomFactor > 0.1)
        zoomFactor -= 0.1;
    updateGL();
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    switch (state) {
    case MOUSE_UP:
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        state = MOUSE_DOWN;
        break;
    default:
        break;
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    switch (state) {
    case MOUSE_DOWN:
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        // grab a point
        // ..........
        // ..........
        // change mouse state
        state = MOUSE_UP;
        break;
    case MOUSE_DRAGGED:
        state = MOUSE_UP;
        break;
    default:
        break;
    }
    updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){
    switch (state) {
    case MOUSE_DOWN:
        transX -= mouseX - event->pos().x();
        transY -= mouseY - event->pos().y();
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        state = MOUSE_DRAGGED;
        break;
    case MOUSE_DRAGGED:
        transX -= mouseX - event->pos().x();
        transY -= mouseY - event->pos().y();
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        state = MOUSE_DRAGGED;
    default:
        break;
    }
    updateGL();
}
