#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
//#include "borderlayout.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    player = new Player(this);
    thePointTracker = new pointtracker(this);
    QPushButton *displayDataBtn = new QPushButton("display data", this);
    connect(displayDataBtn, SIGNAL(clicked()), this, SLOT(openDisplayPlot()));


    QPushButton *exportCSVBtn = new QPushButton("Export CSV Data", this);

    QPushButton *flipVideoBtn = new QPushButton("Flip Video", this);


    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topRow = new QHBoxLayout();
    QHBoxLayout* layout = new QHBoxLayout();
    QVBoxLayout* east = new QVBoxLayout();

    topRow->addWidget(displayDataBtn);
    topRow->addWidget(exportCSVBtn);
    topRow->addWidget(flipVideoBtn);


    player->setMinimumWidth((int) this->width()*3/4);
    thePointTracker->setMinimumWidth((int) this->width()*1/4);
    layout->addWidget(player);
//    player->setSizePolicy();
   // layout->addWidget(displayDataBtn);

    east->addWidget(thePointTracker);

    layout->addLayout(east);

    mainLayout->addLayout(topRow, 3);
    mainLayout->addLayout(layout);
//    layout->addWidget(createLabel("South"), BorderLayout::South);
//    layout->addWidget(createLabel("East 2"), BorderLayout::East);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    MainWindow::setCentralWidget(window);
}

/*void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::RightArrow) {
        player->frameUp();QHBoxLayout
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
