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
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QComboBox>
#include "Model/realscene.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    // Menu UI
    // QMenu *menuFile, *menuTools, *menuHelp;
    // QAction *actionOpen, *actionSave, *actionExit;
    // QAction *actionDocumentation, *actionAbout;
    // QMenu *menuToolbars;
    // QAction *actionVisualizationOptions, *actionSimulationOptions;

    // ToolBar
    /// iconFinder sur internet!!!!

    // Options UI
    // QWidget *dockWidgetSimOptions, *dockWidgetVisuOptions;
    // QDoubleSpinBox *doubleSpinBoxTime, *doubleSpinBoxPas;
    // QComboBox *comboBoxTime, *comboBoxPas;

    // Player UI
    // QHBoxLayout *layoutPlayer;

    // Scene
    // QVBoxLayout *glLayout;
    // QWidget *centralWidget;
    QGLWidget *qglscene;
    RealScene *realScene;
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

private slots:
    void on_actionExit_triggered();
    void slot_radioButtonToogled(bool checked);
};

#endif // MAINWINDOW_H
