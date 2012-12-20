#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    /*scene2 = new QGraphicsScene( 85, 36, 100, 100, this); // création de la scène

    vue = new QGraphicsView(scene2, this); // création de la vue de la scène

    layFen = new QGridLayout(this);
    layFen->addWidget(vue, 0, 0); // le jeu

    this->centralWidget()->setLayout(layFen);
    */
    //scene2 = new QWidget();
    //QButton *test = new QButton("COUCOU");
    //render->addWidget(scene2);
    //this->centralWidget()->setLayout(layFen);

    centerArea = new QWidget();
    glLayout = new QVBoxLayout(this);
    scene = new QGLWidget();

    glLayout->addWidget(scene,0,0);
    centerArea->setLayout(glLayout);
    this->setCentralWidget(centerArea);
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
