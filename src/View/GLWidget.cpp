#include <QtGui>
#include <math.h>
#include <iostream>
#include "GLWidget.hpp"
#include <cmath>
#include <QImage>
#include <QTimer>
#include <deque>

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
    zoomFactor = 1.;
    transX = transY = 0.;
    state = MOUSE_UP;
    point1Grabbed = point2Grabbed = trackingSelected = distanceSelected = false;
    trackingDone = distanceDone = false;
    trackingPoint = -1;
    areaSelected = false;

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
        emit(this->updateSlider(step));
        updateGL();
        step++;
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

    float left,right,bottom,top;
    left = -w/2.f;
    right = w/2.f;
    bottom = -h/2.f;
    top = h/2.f;
    glOrtho(left,right,bottom,top,-1,1);

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
    glColor3f(255,255,0);
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
    for (unsigned int i=0 ; i<scene->steps()[step]->punch().size() ; i++){
        point[0] = scene->steps()[step]->punch()[i].first;
        point[1] = scene->steps()[step]->punch()[i].second;
        glVertex2fv(point);
    }
    glEnd();

    // area
    glColor3f(100,255,100);
    unsigned int size = scene->steps()[step]->sheetGeom().size();
    if (areaSelected && step>0){
        deque<pair<double,double> > endArea;
        endArea.push_front(scene->steps()[step]->sheetGeom()[(int) (size/2-1)]);
        endArea.push_front(scene->steps()[0]->sheetGeom()[(int) (size/2)]);
        for (unsigned int i=0 ; i<size/2-1 ; i++){
            glBegin(GL_POLYGON);
                // bot-left
                point[0] = scene->steps()[step]->sheetGeom()[i].first;
                point[1] = scene->steps()[step]->sheetGeom()[i].second;
                glVertex2fv(point);
                // bot-right
                point[0] = scene->steps()[step]->sheetGeom()[i+1].first;
                point[1] = scene->steps()[step]->sheetGeom()[i+1].second;
                glVertex2fv(point);
                //top-right
                point[0] = scene->steps()[0]->sheetGeom()[(size-1)-(i+1)].first;
                point[1] = scene->steps()[0]->sheetGeom()[(size-1)-(i+1)].second;
                glVertex2fv(point);
                // top-left
                point[0] = scene->steps()[0]->sheetGeom()[(size-1)-i].first;
                point[1] = scene->steps()[0]->sheetGeom()[(size-1)-i].second;
                glVertex2fv(point);
                // bot-left
                point[0] = scene->steps()[step]->sheetGeom()[i].first;
                point[1] = scene->steps()[step]->sheetGeom()[i].second;
                glVertex2fv(point);
            glEnd();
        }
        for (int i=0; i<step ; i++){
            endArea.push_front(scene->steps()[i]->sheetGeom()[size/2-1]);
        }
        endArea.push_front(scene->steps()[step]->sheetGeom()[(int) (size/2-1)]);
        glBegin(GL_POLYGON);
        for (deque<pair<double,double> >::iterator i=endArea.begin(); i!=endArea.end() ; ++i){
                point[0] = (*i).first;
                point[1] = (*i).second;
                glVertex2fv(point);
            }
        glEnd();
    }

    // metal strip

    glColor3f(0,255,0);
    // affichage du polygone scene->sheetGeom()[step]...
    for (unsigned int i=0 ; i<size/2-1 ; i++){
        glBegin(GL_POLYGON);
            // bot-left
            point[0] = scene->steps()[step]->sheetGeom()[i].first;
            point[1] = scene->steps()[step]->sheetGeom()[i].second;
            glVertex2fv(point);
            // bot-right
            point[0] = scene->steps()[step]->sheetGeom()[i+1].first;
            point[1] = scene->steps()[step]->sheetGeom()[i+1].second;
            glVertex2fv(point);
            //top-right
            point[0] = scene->steps()[step]->sheetGeom()[(size-1)-(i+1)].first;
            point[1] = scene->steps()[step]->sheetGeom()[(size-1)-(i+1)].second;
            glVertex2fv(point);
            // top-left
            point[0] = scene->steps()[step]->sheetGeom()[(size-1)-i].first;
            point[1] = scene->steps()[step]->sheetGeom()[(size-1)-i].second;
            glVertex2fv(point);
            // bot-left
            point[0] = scene->steps()[step]->sheetGeom()[i].first;
            point[1] = scene->steps()[step]->sheetGeom()[i].second;
            glVertex2fv(point);
        glEnd();
    }
    //cout << step << endl;

    // neutral fiber
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    for (unsigned int i=0 ; i<scene->steps()[step]->sheetNeut().size()-1 ; i++){
        point[0] = scene->steps()[step]->sheetNeut()[i].first;
        point[1] = scene->steps()[step]->sheetNeut()[i].second;
        glVertex2fv(point);
        point[0] = scene->steps()[step]->sheetNeut()[i+1].first;
        point[1] = scene->steps()[step]->sheetNeut()[i+1].second;
        glVertex2fv(point);
    }
    glEnd();
    
    // interactions
    glPointSize(5.f);
    if(point2Grabbed){
        glBegin(GL_POINTS);
            glColor3f(255,255,255);
            glVertex2fv(point2);
        glEnd();
    }
    // visualize tracking
    if (trackingSelected && trackingDone){
        glColor3f(255,255,255);
        glBegin(GL_POINTS);
            point[0] = scene->steps()[step]->sheetGeom()[trackingPoint].first;
            point[1] = scene->steps()[step]->sheetGeom()[trackingPoint].second;
            glVertex2fv(point);
        glEnd();
        for (int i=0; i<step-1 ; i++){
            glBegin(GL_LINES);
                point[0] = scene->steps()[i]->sheetGeom()[trackingPoint].first;
                point[1] = scene->steps()[i]->sheetGeom()[trackingPoint].second;
                glVertex2fv(point);
                point[0] = scene->steps()[i+1]->sheetGeom()[trackingPoint].first;
                point[1] = scene->steps()[i+1]->sheetGeom()[trackingPoint].second;
                glVertex2fv(point);
            glEnd();
        }
    }



    //visualize distance
    if (distanceSelected){
        if(point1Grabbed){
            glBegin(GL_POINTS);
                glColor3f(255,255,255);
                glVertex2fv(point1);
            glEnd();
        }
        if (distanceDone){
            glBegin(GL_POINTS);
                glColor3f(255,255,255);
                glVertex2fv(point2);
            glEnd();
            glBegin(GL_LINES);
                glVertex2fv(point1);
                glVertex2fv(point2);
            glEnd();
        }
    }

    glPopMatrix();
}

void GLWidget::wheelEvent(QWheelEvent *event){
    if (state == MOUSE_UP){
        if (event->delta() > 0)
            zoomFactor += 0.2;
        else if(zoomFactor > 0.2)
            zoomFactor -= 0.2;
        updateGL();
    }
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    switch (state) {
    case MOUSE_UP:
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        if (distanceSelected){
            if (trackingDone){
                point1Grabbed = false;
                trackingDone = false;
            }
            if (distanceDone){
                point1Grabbed = false;
                point2Grabbed = false;
                distanceDone = false;
            }
        }
        if (trackingSelected){
            if (distanceDone){
                point1Grabbed = false;
                point2Grabbed = false;
                distanceDone = false;
            }
            if (trackingDone){
                point1Grabbed = false;
                trackingDone = false;
            }
        }

        state = MOUSE_DOWN;
        updateGL();
        break;
    default:
        break;
    }
}
bool GLWidget::grab_point(float mouseX, float mouseY, float *point){
    float w = (float) width()/zoomFactor;
    float h = (float) height()/zoomFactor;
    w = w/2.;
    h = h/2.;
    point[0] = mouseX/zoomFactor - w - transX/zoomFactor;
    point[1] = (height()-mouseY)/zoomFactor - h + transY/zoomFactor;
    return true;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event){
    switch (state) {
    case MOUSE_DOWN:
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        if (trackingSelected){
            // grab a point
            if (!point1Grabbed){
                point1Grabbed = grab_point(mouseX,mouseY,point1);
                emit(point_a_afficher(point1[0],point1[1]));
            }
            if (point1Grabbed) {
                //scene->compute_tracking(point1);
                trackingDone = true;
                //emit(tracking(point1[0],point1[1], step)); // scene.compute_tracking(point1);
            }
            // ----------------------
            cout << "I'm tracking : " << endl;
            cout << "trackingSelected : " << trackingSelected << endl;
            cout << "trackingDone : " << trackingDone << endl;
            cout << "distanceSelected : " << distanceSelected << endl;
            cout << "distanceDone : " << distanceDone << endl;
            if (trackingDone)
                cout << "point1 : (" << point1[0] << ", " << point1[1] << ")" << endl;
            cout << endl;
            // ----------------------
        }
        else if (distanceSelected){
            trackingDone = false;
            // grab a point
            if (!point1Grabbed){
                point1Grabbed = grab_point(mouseX,mouseY,point1);
                emit(point_a_afficher(point1[0],point1[1]));
            }
            else if (point1Grabbed && !point2Grabbed) {
                point2Grabbed = grab_point(mouseX,mouseY,point2);
            }
            if (point2Grabbed){
                //scene->compute_distance(point1, point2);
                distanceDone = true;
                emit(calculerDistance(point1[0],point1[1],point2[0],point2[1]));
            }
            // -------------------------
            cout << "I'm distancing : " << endl;
            cout << "trackingSelected : " << trackingSelected << endl;
            cout << "trackingDone : " << trackingDone << endl;
            cout << "distanceSelected : " << distanceSelected << endl;
            cout << "distanceDone : " << distanceDone << endl;
            if (distanceDone){
                cout << "point1 : (" << point1[0] << ", " << point1[1] << ")" << endl;
                cout << "point2 : (" << point2[0] << ", " << point2[1] << ")" << endl;
            }
            cout << endl;
            // -------------------------
        }
        else{
            cout << "I'm doing nothing : " << endl;
            cout << "trackingSelected : " << trackingSelected << endl;
            cout << "trackingDone : " << trackingDone << endl;
            cout << "distanceSelected : " << distanceSelected << endl;
            cout << "distanceDone : " << distanceDone << endl;
            cout << endl;
        }
        // change mouse state
        state = MOUSE_UP;
        updateGL();
        break;
    case MOUSE_DRAGGED:
        state = MOUSE_UP;
        updateGL();
        break;
    default:
        break;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event){

    float dx = mouseX - event->pos().x();
    float dy = mouseY - event->pos().y();

    switch (state) {
    case MOUSE_DOWN:
        transX -= dx;
        transY -= dy;
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        state = MOUSE_DRAGGED;
        updateGL();
        break;
    case MOUSE_DRAGGED:
        transX -= dx;
        transY -= dy;
        mouseX = event->pos().x();
        mouseY = event->pos().y();
        state = MOUSE_DRAGGED;
        updateGL();
    default:
        break;
    }
}

