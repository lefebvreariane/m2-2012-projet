#include <QtGui>
#include <math.h>
#include <iostream>
#include "GLWidget.hpp"
#include <cmath>
#include <QImage>
#include <QTimer>

using namespace std;

GLWidget::GLWidget(float _span, unsigned int _nbStep, Scene *_scene, QWidget *parent):
    QGLWidget(parent),
    scene(_scene),
    step(0),
    nbStep(_nbStep),
    span(_span){
    // bounding box
    pair<pair<float,float> ,pair<float,float> > boundingBox = scene->min_max();
    pMin = boundingBox.first;
    pMax = boundingBox.second;
    resizeGL(500,500);


    mesh = scene->triangleMatrix();
//    cout << "taille: " << mesh.size() << endl;

    // interactions souris
    zoomFactor = 1;
    transX = transY = 0;
    state = MOUSE_UP;
    point1Grabbed = point2Grabbed = trackingSelected = distanceSelected = false;
    trackingDone = false;

    // start timer
    timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));

}

GLWidget::~GLWidget(){
    if (timer->isActive())
        timer->stop();
    delete timer;
}

bool GLWidget::is_timer_active(){
    return timer->isActive();
}

void GLWidget::updateTime(){
    if (step < nbStep){
        step += 1;
        emit(this->updateSlider(step));
        updateGL();
    }
    else{
        timer->stop();
        emit(this->updateSlider(step));
    }
}

void GLWidget::start_timer(int _step){
    step = _step;
    timer->start(span);
}

int GLWidget::stop_timer(){
    timer->stop();
    return step;
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
    for (unsigned int i=0 ; i<scene->matrix().size() ; i++){
        point[0] = scene->matrix()[i].first;
        point[1] = scene->matrix()[i].second;
        glVertex2fv(point);
    }
    glEnd();
    /*
    glBegin(GL_TRIANGLES);
    for (unsigned int i=0 ; i<mesh.size() ; i++){
        point[0] = mesh[i][0].first;
        point[1] = mesh[i][0].second;
        glVertex2fv(point);
        point[0] = mesh[i][2].first;
        point[1] = mesh[i][2].second;
        glVertex2fv(point);
        point[0] = mesh[i][1].first;
        point[1] = mesh[i][1].second;
        glVertex2fv(point);
    }
    glEnd();
    glBegin(GL_POINTS);
    for (unsigned int i=0 ; i<mesh.size() ; i++){
        point[0] = mesh[i][0].first;
        point[1] = mesh[i][0].second;
        cout << point[0] << ", " << point[1] << endl;
        glVertex2fv(point);
        point[0] = mesh[i][2].first;
        point[1] = mesh[i][2].second;
        glVertex2fv(point);
        point[0] = mesh[i][1].first;
        point[1] = mesh[i][1].second;
        glVertex2fv(point);
    }
    glEnd();
    */

    // strippers
    glColor3f(100,100,100);
    for (unsigned int i=0 ; i<scene->strippers().size() ; i++){
        glBegin(GL_POLYGON);
        for (unsigned int j=0 ; j<scene->strippers()[i].second.size() ; j++){
            point[0] = scene->strippers()[i].second[j].first;
            point[1] = scene->strippers()[i].second[j].second;
            glVertex2fv(point);
        }
        glEnd();
    }

    // punch
    glColor3f(0,0,255);
    glBegin(GL_POLYGON);
    // affichage du polygone scene->punch()[step]...
    for (unsigned int i=0 ; i<scene->punch().first.size() ; i++){
        point[0] = scene->punch().first[i].first;
        point[1] = scene->punch().first[i].second;
        glVertex2fv(point);
    }
    glEnd();

    // metal strip
    glColor3f(0,255,0);
    glBegin(GL_POLYGON);
    // affichage du polygone scene->sheet()[step]...
    for (unsigned int i=0 ; i<scene->sheet().second.size() ; i++){
        point[0] = scene->sheet().second[i].first;
        point[1] = scene->sheet().second[i].second;
        glVertex2fv(point);
    }
    glEnd();
    glPopMatrix();
    glPointSize(0.5f);
    if(point1Grabbed){
        glBegin(GL_POINTS);
            glColor3f(255,255,255);
            glVertex2fv(point1);
        glEnd();
    }
    if(point2Grabbed){
        glBegin(GL_POINTS);
            glColor3f(255,255,255);
            glVertex2fv(point2);
        glEnd();
    }
    // visualize tracking
    if (trackingDone){
        // TODO
    }

    //visualize distance
    if (distanceDone){
        glBegin(GL_POINTS);
            glColor3f(255,255,255);
            glVertex2fv(point1);
            glVertex2fv(point2);
        glEnd();
        glBegin(GL_LINES);
            glVertex2fv(point1);
            glVertex2fv(point2);
        glEnd();
    }
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
bool GLWidget::grab_point(float mouseX, float mouseY, float *point){
    double mvMatrix[16];
    double projMatrix[16];
    int viewPort[4];
    glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    glGetIntegerv(GL_VIEWPORT, viewPort);
    return gluUnProject((double) mouseX, (double) mouseY,0.,
                          mvMatrix, projMatrix, viewPort,
                          (double *) &(point[0]), (double *) &(point[1]), (double *) &(point[2]));
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    switch (state) {
    case MOUSE_DOWN:
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        if (trackingSelected){
            distanceDone = false;
            // grab a point
            if (!point1Grabbed)
                point1Grabbed = grab_point(mouseX,mouseY,point1);
            else {
                //scene->compute_tracking(point1);
                trackingDone = true;
                point1Grabbed = false;
            }
        }
        else if (distanceSelected){
            trackingDone = false;
            // grab a point
            if (!point1Grabbed){
                point1Grabbed = grab_point(mouseX,mouseY,point1);
            }
            else {
                point2Grabbed = grab_point(mouseX,mouseY,point2);
            }
            if (point2Grabbed){
                //scene->compute_distance(point1, point2);
                distanceDone = true;
                point1Grabbed = point2Grabbed = false;
            }
        }
        else {
            point1Grabbed = false;
            point2Grabbed = false;
            trackingDone = false;
            distanceDone = false;
        }

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

    float dx = mouseX - event->pos().x();
    float dy = mouseY - event->pos().y();

    switch (state) {
    case MOUSE_DOWN:
        if (dx > 2 && dy > 2){
            transX -= dx;
            transY -= dy;
            mouseX = event->pos().x();
            mouseY = event->pos().y();
            state = MOUSE_DRAGGED;
        }
        break;
    case MOUSE_DRAGGED:
        transX -= dx;
        transY -= dy;
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        state = MOUSE_DRAGGED;
    default:
        break;
    }
    updateGL();
}

