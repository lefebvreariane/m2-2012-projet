#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Controler/Visualization.hpp"
#include <iostream>
#include <sstream>
#include <QAction>
#include <QTimer>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), scene("../scenes/sceneTest1.xml"),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // menu
    QAction *actionSimulationOptions = new QAction("Show Simulation Options", this);
    actionSimulationOptions = ui->dockWidgetSimulationOptions->toggleViewAction();
    connect(ui->actionSimulationOptions, SIGNAL(toggled(bool)), ui->dockWidgetSimulationOptions, SLOT(setVisible(bool)));
    QAction *actionPlayerOptions = new QAction("Show Player Options", this);
    actionPlayerOptions = ui->dockWidgetPlayerOptions->toggleViewAction();
    connect(ui->actionPlayerOptions, SIGNAL(toggled(bool)), ui->dockWidgetPlayerOptions, SLOT(setVisible(bool)));
    ui->menuToolbars->addAction(actionSimulationOptions);
    ui->menuToolbars->addAction(actionPlayerOptions);

    // Player
    ui->pushButtonFirst->setIcon(QIcon("../View/img/First.png"));
    ui->pushButtonLast->setIcon(QIcon("../View/img/Last.png"));
    ui->pushButtonPlay->setIcon(QIcon("../View/img/Play.png"));
    ui->pushButtonPause->setIcon(QIcon("../View/img/Pause.png"));

    // scene
    //scene = Scene("../scenes/sceneTest1.xml");
    visualization = new Visualization(ui->spinBoxTime->value(),ui->spinBoxTotalTime->value()*1000);
    glWidget = new GLWidget(ui->spinBoxTime->value(), visualization->timeVector().size(),&(visualization->scene), this);
    connect(glWidget,SIGNAL(updateSlider(int)),this,SLOT(slot_uiUpdateStep(int)));
    connect(glWidget,SIGNAL(point_a_afficher(float,float)),this,SLOT(slot_update_status(float,float)));
    connect(glWidget,SIGNAL(calculerDistance(float,float,float,float)),this,SLOT(slot_update_status(float,float,float,float)));
    ui->glLayout->addWidget(glWidget,0,0);
}

MainWindow::~MainWindow()
{
    delete visualization;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/////////////////////////////////////////////
// SLOTS ////////////////////////////////////
/////////////////////////////////////////////

void MainWindow::on_actionExit_triggered()
{
   close();
}

void MainWindow::slot_pushButtonStartClicked(){
    ui->pushButtonStartCalculation->setText("Calcul in process ...");
    ui->pushButtonStartCalculation->setEnabled(false);
    ui->pushButtonFirst->setEnabled(false);
    ui->pushButtonLast->setEnabled(false);
    ui->pushButtonPause->setEnabled(false);
    ui->pushButtonPlay->setEnabled(false);
    ui->spinBoxEtapes->setMaximum(visualization->totalTime()/visualization->span());
    ui->sliderEtapes->setMaximum(ui->spinBoxEtapes->maximum());
    // Start calcul

    // Fin calcul
    ui->pushButtonPlay->setEnabled(true);
    ui->pushButtonPlay->setFocus();
    ui->pushButtonFirst->setEnabled(true);
    ui->pushButtonLast->setEnabled(true);
    ui->pushButtonStartCalculation->setEnabled(true);
    ui->sliderEtapes->setEnabled(true);
    ui->spinBoxEtapes->setEnabled(true);
    ui->pushButtonStartCalculation->setText("Start");
}

void MainWindow::slot_stepChanged(int step){
    glWidget->set_step(step-1);
}
void MainWindow::slot_pushButtonPauseClicked(){
    glWidget->stop_timer();
    ui->pushButtonFirst->setEnabled(true);
    ui->pushButtonLast->setEnabled(true);
    ui->pushButtonPlay->setEnabled(true);
    ui->pushButtonPause->setEnabled(false);
    ui->sliderEtapes->setEnabled(true);
    ui->spinBoxEtapes->setEnabled(true);
    glWidget->set_step(ui->spinBoxEtapes->value()-1);
}
void MainWindow::slot_pushButtonPlayClicked(){
    ui->pushButtonPlay->setEnabled(false);
    ui->pushButtonPause->setEnabled(true);
    ui->pushButtonFirst->setEnabled(false);
    ui->pushButtonLast->setEnabled(false);
    ui->sliderEtapes->setEnabled(false);
    ui->spinBoxEtapes->setEnabled(false);

    //if (glWidget->point1Grabbed)
    //    scene.tracking(glWidget->getPoint1(),ui->spinBoxEtapes->value()-1);
    glWidget->start_timer(ui->sliderEtapes->value()-1);
}
void MainWindow::slot_pushButtonFirstClicked(){
    glWidget->set_step(0);
    ui->spinBoxEtapes->setValue(1);
}
void MainWindow::slot_pushButtonLastClicked(){
    glWidget->set_step(ui->spinBoxEtapes->maximum()-1);
    ui->spinBoxEtapes->setValue(ui->spinBoxEtapes->maximum());
}

void MainWindow::slot_uiUpdateStep(int step){
    if (glWidget->is_timer_active()){
        ui->spinBoxEtapes->setValue(step);
    }
    else
        this->slot_pushButtonPauseClicked();
}

void MainWindow::on_actionPointTracking_toggled(bool checked){
    if (checked){
        glWidget->trackingSelected = true;
        glWidget->point1Grabbed = false;
        glWidget->distanceSelected = false;
        ui->actionDistance->setChecked(false);
    }
    else{
        glWidget->trackingSelected = false;
        glWidget->point1Grabbed = false;
    }
    glWidget->updateGL();
}


void MainWindow::on_actionDistance_toggled(bool checked){
    if (checked){
        glWidget->distanceSelected = true;
        glWidget->point1Grabbed = false;
        glWidget->point2Grabbed = false;
        glWidget->trackingSelected = false;
        ui->actionPointTracking->setChecked(false);
    }
    else{
        glWidget->distanceSelected = false;
        glWidget->point1Grabbed = false;
        glWidget->point2Grabbed = false;
    }
    glWidget->updateGL();
}


void MainWindow::slot_update_status(float x1, float y1, float x2, float y2){
    stringstream s;
    s << "Point 1 = (" << x1 << ", " << y1 << ")    ";
    s << "Point 2 = (" << x2 << ", " << y2 << ")    ";
    s << "Distance = " << sqrt(pow(x2-x1,2) + pow(y2-y1,2));
    QString ss = QString::fromStdString(s.str());
    statusBar()->showMessage(ss);
}

void MainWindow::slot_update_status(float x1, float y1){
    stringstream s;
    if(glWidget->trackingSelected){
        s << "Point to track = (" << x1 << ", " << y1 << ")";
    }
    else
        s << "Point 1 = (" << x1 << ", " << y1 << ")";
    QString ss = QString::fromStdString(s.str());
    statusBar()->showMessage(ss);
}
