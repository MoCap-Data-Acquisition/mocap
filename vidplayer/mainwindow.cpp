#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new Player;
    QPushButton *displayDataBtn = new QPushButton("display data", this);
    connect(displayDataBtn, SIGNAL(clicked()), this, SLOT(openDisplayPlot()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(player);
    layout->addWidget(displayDataBtn);



    QWidget *window = new QWidget();
    window->setLayout(layout);
    MainWindow::setCentralWidget(window);
}

/*void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::RightArrow) {
        player->frameUp();
        event->accept();
    } else if (event->key() == Qt::LeftArrow) {
        player->frameDown();
        event->accept();QCustomPlot *customPlot, const QVector<qint64> &v1, const QVector<qint64> &v2
    } else {
        MainWindow::keyPressEvent(event);
    }
}*/

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openDisplayPlot()
{
    displayPlotWindow.setupDisplayTest();
    displayPlotWindow.show();
}
