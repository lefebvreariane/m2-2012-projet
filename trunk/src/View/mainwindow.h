#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMdiArea>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QGLWidget>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    QMenu *menuFile, *menuTools, *menuHelp;
    QMenu *menuToolbars; /// iconFinder sur internet!!!!
    QAction *actionOpen, *actionSave, *actionExit;
    QAction *actionVisualize;
    QAction *actionDocumentation, *actionAbout;

    QVBoxLayout *glLayout;
    QGLWidget *scene;
    QWidget *centerArea;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:

private slots:
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
