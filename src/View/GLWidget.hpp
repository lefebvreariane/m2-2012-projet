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


class GLWidget : public QGLWidget{
    Q_OBJECT

public:
    Scene scene;

    GLWidget(float _span, unsigned int nbStep, Scene _scene, QWidget *parent = 0);
    ~GLWidget();

protected:
    float step;
    unsigned int nbStep;
    float span;
    float yInit;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void afficherScene();
    void paintEvent(QPaintEvent *event);

public slots:
    void updateTime();

private:
    QTimer* timer;

};


#endif // GLWIDGET_HPP
