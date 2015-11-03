#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"
#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Player* player = new Player;
    QPushButton *displayDataBtn = new QPushButton("display data", this);
    connect(displayDataBtn, SIGNAL(clicked()), this, SLOT(openDisplayPlot()));


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(player);
    layout->addWidget(displayDataBtn);



    QWidget *window = new QWidget();
    window->setLayout(layout);
    MainWindow::setCentralWidget(window);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openDisplayPlot()
{
    displayPlotWindow = new PlotWindow();
    displayPlotWindow->show();
}
