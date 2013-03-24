#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

//#include <Controler/simulation.hpp>

#include <QMainWindow>
#include <QMenu>
#include <QAction>
#include <QMdiArea>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QMessageBox>
#include "View/GLWidget.hpp"
#include "Model/scene.h"
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QComboBox>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:

    // ToolBar
    /// iconFinder sur internet!!!!

    GLWidget *glWidget;
    Scene scene;

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Visualization *visualization;
    Ui::MainWindow *ui;

private slots:
    void on_actionDistance_toggled(bool checked);
    void on_actionPointTracking_toggled(bool checked);
    void on_actionExit_triggered();
    void slot_pushButtonStartClicked();
    void slot_pushButtonPlayClicked();
    void slot_pushButtonPauseClicked();
    void slot_pushButtonFirstClicked();
    void slot_pushButtonLastClicked();
    void slot_uiUpdateStep(int step);
    void slot_update_status(float x1,float y1);
    void slot_update_status(float x1,float y1,float x2,float y2);
    void slot_update_glStep(int _step);
};

#endif // MAINWINDOW_HPP
