#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "Controler/Visualization.hpp"
#include <iostream>
#include <QAction>

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

    // scene
    float span = 1;
    float totalTime = 30;
    //scene = Scene("../scenes/sceneTest1.xml");
    visualization = new Visualization(span,totalTime);
    glWidget = new GLWidget(span, visualization->timeVector().size(),visualization->scene(), this);
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
    QMessageBox *popupSave = new QMessageBox();
    popupSave->setVisible(true);
    popupSave->setText("The document has been modified.");
    popupSave->setInformativeText("Do you want to save your changes?");
    popupSave->setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    popupSave->setDefaultButton(QMessageBox::Save);
    int ret = popupSave->exec();
    switch (ret) {
    case QMessageBox::Save:
        // Save was clicked
        close();
        break;
    case QMessageBox::Discard:
        // Don't Save was clicked
        close();
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        break;
    default:
        // should never be reached
        break;
    }
}

void MainWindow::slot_radioButtonToogled(bool checked){

    ui->comboBoxTime->setEnabled(checked);
    ui->doubleSpinBoxTime->setEnabled(checked);

    ui->comboBoxPas->setEnabled(!checked);
    ui->doubleSpinBoxPas->setEnabled(!checked);
}

void MainWindow::slot_pushButtonStartCancelToogled(){
    if (ui->pushButtonCancel->isEnabled()){
        // The cancel button has just been toogled
        ui->pushButtonStartCalculation->setEnabled(true);
        ui->pushButtonCancel->setEnabled(false);
    }
    else{
        ui->pushButtonStartCalculation->setEnabled(false);
        ui->pushButtonCancel->setEnabled(true);
    }
}
