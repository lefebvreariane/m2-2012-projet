#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Controler/Visualization.hpp"
#include <iostream>
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
