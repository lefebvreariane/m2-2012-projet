#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->centralWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    cout << "coucou1" << endl;
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

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
