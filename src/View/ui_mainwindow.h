/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jan 23 11:15:08 2013
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
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QRadioButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
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
    QAction *actionSimulationOptions;
    QAction *actionVisualizationOptions;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *glLayout;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuToolbars;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidgetSimulationOptions;
    QWidget *dockWidgetSimOptions;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButtonPas;
    QHBoxLayout *horizontalLayoutPas;
    QDoubleSpinBox *doubleSpinBoxPas;
    QComboBox *comboBoxPas;
    QRadioButton *radioButtonTime;
    QHBoxLayout *horizontalLayoutTime;
    QDoubleSpinBox *doubleSpinBoxTime;
    QComboBox *comboBoxTime;
    QDockWidget *dockWidgetVisualizationOptions;
    QWidget *dockWidgetVisuOptions;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayoutEtapes;
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
        actionSimulationOptions = new QAction(MainWindow);
        actionSimulationOptions->setObjectName(QString::fromUtf8("actionSimulationOptions"));
        actionSimulationOptions->setCheckable(true);
        actionSimulationOptions->setChecked(true);
        actionVisualizationOptions = new QAction(MainWindow);
        actionVisualizationOptions->setObjectName(QString::fromUtf8("actionVisualizationOptions"));
        actionVisualizationOptions->setCheckable(true);
        actionVisualizationOptions->setChecked(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setAutoFillBackground(false);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        glLayout = new QVBoxLayout();
        glLayout->setSpacing(6);
        glLayout->setObjectName(QString::fromUtf8("glLayout"));

        horizontalLayout->addLayout(glLayout);

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
        dockWidgetSimulationOptions->setMinimumSize(QSize(239, 159));
        dockWidgetSimulationOptions->setAcceptDrops(false);
        dockWidgetSimulationOptions->setAutoFillBackground(true);
        dockWidgetSimulationOptions->setFloating(false);
        dockWidgetSimOptions = new QWidget();
        dockWidgetSimOptions->setObjectName(QString::fromUtf8("dockWidgetSimOptions"));
        dockWidgetSimOptions->setMinimumSize(QSize(239, 0));
        verticalLayout_2 = new QVBoxLayout(dockWidgetSimOptions);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        radioButtonPas = new QRadioButton(dockWidgetSimOptions);
        radioButtonPas->setObjectName(QString::fromUtf8("radioButtonPas"));
        radioButtonPas->setChecked(true);
        radioButtonPas->setAutoExclusive(true);

        verticalLayout_2->addWidget(radioButtonPas);

        horizontalLayoutPas = new QHBoxLayout();
        horizontalLayoutPas->setSpacing(6);
        horizontalLayoutPas->setObjectName(QString::fromUtf8("horizontalLayoutPas"));
        doubleSpinBoxPas = new QDoubleSpinBox(dockWidgetSimOptions);
        doubleSpinBoxPas->setObjectName(QString::fromUtf8("doubleSpinBoxPas"));
        doubleSpinBoxPas->setEnabled(true);
        doubleSpinBoxPas->setMinimumSize(QSize(0, 25));
        doubleSpinBoxPas->setMaximumSize(QSize(16777215, 25));

        horizontalLayoutPas->addWidget(doubleSpinBoxPas);

        comboBoxPas = new QComboBox(dockWidgetSimOptions);
        comboBoxPas->setObjectName(QString::fromUtf8("comboBoxPas"));
        comboBoxPas->setEnabled(true);
        comboBoxPas->setMinimumSize(QSize(0, 25));
        comboBoxPas->setMaximumSize(QSize(16777215, 25));

        horizontalLayoutPas->addWidget(comboBoxPas);


        verticalLayout_2->addLayout(horizontalLayoutPas);

        radioButtonTime = new QRadioButton(dockWidgetSimOptions);
        radioButtonTime->setObjectName(QString::fromUtf8("radioButtonTime"));
        radioButtonTime->setChecked(false);

        verticalLayout_2->addWidget(radioButtonTime);

        horizontalLayoutTime = new QHBoxLayout();
        horizontalLayoutTime->setSpacing(6);
        horizontalLayoutTime->setObjectName(QString::fromUtf8("horizontalLayoutTime"));
        doubleSpinBoxTime = new QDoubleSpinBox(dockWidgetSimOptions);
        doubleSpinBoxTime->setObjectName(QString::fromUtf8("doubleSpinBoxTime"));
        doubleSpinBoxTime->setEnabled(false);
        doubleSpinBoxTime->setMinimumSize(QSize(0, 25));
        doubleSpinBoxTime->setMaximumSize(QSize(16777215, 25));
        doubleSpinBoxTime->setMaximum(5000);

        horizontalLayoutTime->addWidget(doubleSpinBoxTime);

        comboBoxTime = new QComboBox(dockWidgetSimOptions);
        comboBoxTime->setObjectName(QString::fromUtf8("comboBoxTime"));
        comboBoxTime->setEnabled(false);
        comboBoxTime->setMinimumSize(QSize(0, 25));
        comboBoxTime->setMaximumSize(QSize(16777215, 25));

        horizontalLayoutTime->addWidget(comboBoxTime);


        verticalLayout_2->addLayout(horizontalLayoutTime);

        dockWidgetSimulationOptions->setWidget(dockWidgetSimOptions);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetSimulationOptions);
        dockWidgetVisualizationOptions = new QDockWidget(MainWindow);
        dockWidgetVisualizationOptions->setObjectName(QString::fromUtf8("dockWidgetVisualizationOptions"));
        dockWidgetVisuOptions = new QWidget();
        dockWidgetVisuOptions->setObjectName(QString::fromUtf8("dockWidgetVisuOptions"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetVisuOptions);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayoutEtapes = new QHBoxLayout();
        horizontalLayoutEtapes->setSpacing(6);
        horizontalLayoutEtapes->setObjectName(QString::fromUtf8("horizontalLayoutEtapes"));
        sliderEtapes = new QSlider(dockWidgetVisuOptions);
        sliderEtapes->setObjectName(QString::fromUtf8("sliderEtapes"));
        sliderEtapes->setEnabled(false);
        sliderEtapes->setMinimumSize(QSize(0, 25));
        sliderEtapes->setMaximumSize(QSize(16777215, 25));
        sliderEtapes->setOrientation(Qt::Horizontal);

        horizontalLayoutEtapes->addWidget(sliderEtapes);

        spinBoxEtapes = new QSpinBox(dockWidgetVisuOptions);
        spinBoxEtapes->setObjectName(QString::fromUtf8("spinBoxEtapes"));
        spinBoxEtapes->setEnabled(false);
        spinBoxEtapes->setMinimumSize(QSize(0, 25));
        spinBoxEtapes->setMaximumSize(QSize(16777215, 25));

        horizontalLayoutEtapes->addWidget(spinBoxEtapes);


        verticalLayout_3->addLayout(horizontalLayoutEtapes);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        dockWidgetVisualizationOptions->setWidget(dockWidgetVisuOptions);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidgetVisualizationOptions);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(menuToolbars->menuAction());
        menuToolbars->addAction(actionSimulationOptions);
        menuToolbars->addAction(actionVisualizationOptions);
        menuHelp->addAction(actionDocumentation);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);
        QObject::connect(sliderEtapes, SIGNAL(valueChanged(int)), spinBoxEtapes, SLOT(setValue(int)));
        QObject::connect(spinBoxEtapes, SIGNAL(valueChanged(int)), sliderEtapes, SLOT(setValue(int)));
        QObject::connect(radioButtonTime, SIGNAL(toggled(bool)), MainWindow, SLOT(slot_radioButtonToogled(bool)));

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
        actionSimulationOptions->setText(QApplication::translate("MainWindow", "Simulation Options", 0, QApplication::UnicodeUTF8));
        actionVisualizationOptions->setText(QApplication::translate("MainWindow", "Visualization Options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        centralWidget->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menuToolbars->setTitle(QApplication::translate("MainWindow", "Toolbars", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        dockWidgetSimulationOptions->setWindowTitle(QApplication::translate("MainWindow", "Simulation Options", 0, QApplication::UnicodeUTF8));
        radioButtonPas->setText(QApplication::translate("MainWindow", "By span length", 0, QApplication::UnicodeUTF8));
        comboBoxPas->clear();
        comboBoxPas->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "mm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "cm", 0, QApplication::UnicodeUTF8)
        );
        radioButtonTime->setText(QApplication::translate("MainWindow", "By visualization time", 0, QApplication::UnicodeUTF8));
        comboBoxTime->clear();
        comboBoxTime->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "ms", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "s", 0, QApplication::UnicodeUTF8)
        );
        dockWidgetVisualizationOptions->setWindowTitle(QApplication::translate("MainWindow", "Visualisation Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
