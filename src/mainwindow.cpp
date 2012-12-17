#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    //if (textEdit->isWindowModified()){
         QMessageBox *popupSave = new QMessageBox();
         popupSave->setVisible(true);
    //}
    //tabWidget->removeTab(index);
}
