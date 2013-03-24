#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#if defined ( __APPLE__ )
#include <opengl/glu.h>
#endif
#include <QPaintEvent>
#include <QGLWidget>
#include <QTime>
#include "Model/scene.h"
#include "Controler/Visualization.hpp"

enum MouseState {MOUSE_UP, MOUSE_DOWN, MOUSE_DRAGGED};

class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    Scene *scene;
    float step;
    bool trackingSelected;
    bool distanceSelected;
    bool areaSelected;
    bool point1Grabbed;
    bool point2Grabbed;
    int trackingPoint;

    GLWidget(float _span, unsigned int nbStep, Scene *_scene, QWidget *parent = 0);
    ~GLWidget();

    void start_timer(int _step);
    int stop_timer();
    void set_step(int _step) {step = _step; updateGL();}
    float *getPoint1() {return point1;}
    bool is_timer_active();

protected:
    unsigned int nbStep;
    float span;
    std::pair<float,float> pMin;
    std::pair<float,float> pMax;
    std::vector< std::vector< std::pair< double, double > > > mesh;

    // interaction souris
    MouseState state;
    float zoomFactor, transX, transY, mouseX, mouseY;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void afficherScene();
    void paintEvent(QPaintEvent *event);

    // evenements souris
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    bool grab_point(float mouseX, float mouseY, float *point);

public slots:
    void updateTime();
signals:
    void updateSlider(int);
    void calculerDistance(float x1, float y1, float x2, float y2);
    void point_a_afficher(float x1, float y1);
private:
    QTimer* timer;
    float point1[2];
    float point2[2];
    bool trackingDone;
    bool distanceDone;

};


#endif // GLWIDGET_HPP
