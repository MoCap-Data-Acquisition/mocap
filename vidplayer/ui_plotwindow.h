/********************************************************************************
** Form generated from reading UI file 'plotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTWINDOW_H
#define UI_PLOTWINDOW_H

#include <../vidplayer/qcustomplot.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout1;
    QCustomPlot *customPlotX;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout2;
    QCustomPlot *customPlotY;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlotWindow)
    {
        if (PlotWindow->objectName().isEmpty())
            PlotWindow->setObjectName(QStringLiteral("PlotWindow"));
        PlotWindow->resize(800, 600);
        PlotWindow->setAnimated(false);
        centralwidget = new QWidget(PlotWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout1 = new QVBoxLayout(tab);
        verticalLayout1->setObjectName(QStringLiteral("verticalLayout1"));
        customPlotX = new QCustomPlot(tab);
        customPlotX->setObjectName(QStringLiteral("customPlotX"));

        verticalLayout1->addWidget(customPlotX);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout2 = new QVBoxLayout(tab_2);
        verticalLayout2->setObjectName(QStringLiteral("verticalLayout2"));
        customPlotY = new QCustomPlot(tab_2);
        customPlotY->setObjectName(QStringLiteral("customPlotY"));

        verticalLayout2->addWidget(customPlotY);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        PlotWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlotWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        PlotWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlotWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PlotWindow->setStatusBar(statusbar);

        retranslateUi(PlotWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PlotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlotWindow)
    {
        PlotWindow->setWindowTitle(QApplication::translate("PlotWindow", "MainWindow", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("PlotWindow", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("PlotWindow", "Tab 2", 0));
    } // retranslateUi

};

namespace Ui {
    class PlotWindow: public Ui_PlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTWINDOW_H
