#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <iostream>
#include <QAction>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // menu
    QAction *actionSimulationOptions = new QAction("Show Simulation Options", this);
    actionSimulationOptions = ui->dockWidgetSimulationOptions->toggleViewAction();
    connect(ui->actionSimulationOptions, SIGNAL(toggled(bool)), ui->dockWidgetSimulationOptions, SLOT(setVisible(bool)));
    QAction *actionVisualizationOptions = new QAction("Show Visualization Options", this);
    actionVisualizationOptions = ui->dockWidgetVisualizationOptions->toggleViewAction();
    connect(ui->actionVisualizationOptions, SIGNAL(toggled(bool)), ui->dockWidgetVisualizationOptions, SLOT(setVisible(bool)));
    ui->menuToolbars->addAction(actionSimulationOptions);
    ui->menuToolbars->addAction(actionVisualizationOptions);

    // scene
    scene = new QGLWidget();
    ui->glLayout->addWidget(scene,0,0);
}

MainWindow::~MainWindow()
{
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
