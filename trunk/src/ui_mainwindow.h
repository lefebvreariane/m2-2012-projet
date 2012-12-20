/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Dec 19 15:52:16 2012
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionDocumentation;
    QAction *actionAbout;
    QAction *actionVisualize;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuToolbars;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidgetSimulationOptions;
    QWidget *dockWidgetOptions;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBoxOptions;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *layoutPrecision;
    QLabel *labelPrecision;
    QDoubleSpinBox *doubleSpinBoxPrecision;
    QComboBox *comboBoxUnites;
    QHBoxLayout *layoutEtapes;
    QSlider *sliderEtapes;
    QSpinBox *spinBoxEtapes;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(691, 442);
        MainWindow->setMinimumSize(QSize(500, 350));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionDocumentation = new QAction(MainWindow);
        actionDocumentation->setObjectName(QString::fromUtf8("actionDocumentation"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionVisualize = new QAction(MainWindow);
        actionVisualize->setObjectName(QString::fromUtf8("actionVisualize"));
        actionVisualize->setCheckable(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setAutoFillBackground(false);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(50, 50));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame->setPalette(palette);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        textEdit = new QTextEdit(frame);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));

        horizontalLayout->addWidget(textEdit);


        verticalLayout->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 691, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuToolbars = new QMenu(menuTools);
        menuToolbars->setObjectName(QString::fromUtf8("menuToolbars"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidgetSimulationOptions = new QDockWidget(MainWindow);
        dockWidgetSimulationOptions->setObjectName(QString::fromUtf8("dockWidgetSimulationOptions"));
        dockWidgetSimulationOptions->setMinimumSize(QSize(239, 345));
        dockWidgetSimulationOptions->setAcceptDrops(false);
        dockWidgetSimulationOptions->setAutoFillBackground(true);
        dockWidgetSimulationOptions->setFloating(false);
        dockWidgetOptions = new QWidget();
        dockWidgetOptions->setObjectName(QString::fromUtf8("dockWidgetOptions"));
        dockWidgetOptions->setMinimumSize(QSize(239, 0));
        horizontalLayout_3 = new QHBoxLayout(dockWidgetOptions);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBoxOptions = new QGroupBox(dockWidgetOptions);
        groupBoxOptions->setObjectName(QString::fromUtf8("groupBoxOptions"));
        groupBoxOptions->setMinimumSize(QSize(239, 200));
        verticalLayout_3 = new QVBoxLayout(groupBoxOptions);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        layoutPrecision = new QHBoxLayout();
        layoutPrecision->setSpacing(6);
        layoutPrecision->setObjectName(QString::fromUtf8("layoutPrecision"));
        labelPrecision = new QLabel(groupBoxOptions);
        labelPrecision->setObjectName(QString::fromUtf8("labelPrecision"));

        layoutPrecision->addWidget(labelPrecision);

        doubleSpinBoxPrecision = new QDoubleSpinBox(groupBoxOptions);
        doubleSpinBoxPrecision->setObjectName(QString::fromUtf8("doubleSpinBoxPrecision"));

        layoutPrecision->addWidget(doubleSpinBoxPrecision);

        comboBoxUnites = new QComboBox(groupBoxOptions);
        comboBoxUnites->setObjectName(QString::fromUtf8("comboBoxUnites"));

        layoutPrecision->addWidget(comboBoxUnites);


        verticalLayout_3->addLayout(layoutPrecision);

        layoutEtapes = new QHBoxLayout();
        layoutEtapes->setSpacing(6);
        layoutEtapes->setObjectName(QString::fromUtf8("layoutEtapes"));
        sliderEtapes = new QSlider(groupBoxOptions);
        sliderEtapes->setObjectName(QString::fromUtf8("sliderEtapes"));
        sliderEtapes->setOrientation(Qt::Horizontal);

        layoutEtapes->addWidget(sliderEtapes);

        spinBoxEtapes = new QSpinBox(groupBoxOptions);
        spinBoxEtapes->setObjectName(QString::fromUtf8("spinBoxEtapes"));

        layoutEtapes->addWidget(spinBoxEtapes);


        verticalLayout_3->addLayout(layoutEtapes);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addWidget(groupBoxOptions);

        dockWidgetSimulationOptions->setWidget(dockWidgetOptions);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetSimulationOptions);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(menuToolbars->menuAction());
        menuToolbars->addAction(actionVisualize);
        menuHelp->addAction(actionDocumentation);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        actionDocumentation->setText(QApplication::translate("MainWindow", "Documentation", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About ...", 0, QApplication::UnicodeUTF8));
        actionVisualize->setText(QApplication::translate("MainWindow", "Visualize", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        centralWidget->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menuToolbars->setTitle(QApplication::translate("MainWindow", "Toolbars", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        dockWidgetSimulationOptions->setWindowTitle(QApplication::translate("MainWindow", "Simulation", 0, QApplication::UnicodeUTF8));
        groupBoxOptions->setTitle(QApplication::translate("MainWindow", "Etapes", 0, QApplication::UnicodeUTF8));
        labelPrecision->setText(QApplication::translate("MainWindow", "Pr\303\251cision:", 0, QApplication::UnicodeUTF8));
        comboBoxUnites->clear();
        comboBoxUnites->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ms", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "s", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
