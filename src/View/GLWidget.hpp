#ifndef GLWIDGET_HPP
#define GLWIDGET_HPP

#include <QPaintEvent>
#include <QGLWidget>
#include <QTime>
#include <Model/scene.h>


class GLWidget : public QGLWidget{
    Q_OBJECT

public:

    Scene scene;

    GLWidget(Scene _scene, QWidget *parent = 0);
    ~GLWidget();

protected:
    float Time;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void afficherCourbe();
    void paintEvent(QPaintEvent *event);

public slots:
    void updateTime();

private:
    QTimer* timer;

};


#endif // GLWIDGET_HPP
