#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
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
    connect(exportCSVBtn, SIGNAL(clicked()), player->videoWidget, SLOT(exportCSVData()));
    QPushButton *flipVideoBtn = new QPushButton("Flip Video", this);
    connect(flipVideoBtn, SIGNAL(clicked(bool)), player->videoWidget, SLOT(toggleRotateVideo()));
    QPushButton *helpBtn = new QPushButton("Help", this);
    connect(helpBtn, SIGNAL(clicked()), this, SLOT(openHelpMenu()));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topRow = new QHBoxLayout();
    QHBoxLayout* layout = new QHBoxLayout();
    QVBoxLayout* east = new QVBoxLayout();

    topRow->addWidget(displayDataBtn);
    topRow->addWidget(exportCSVBtn);
    topRow->addWidget(flipVideoBtn);
    topRow->addWidget(helpBtn);

//    player->setMinimumWidth((int) this->width()*3/4);
    thePointTracker->setMinimumWidth((int) this->width()*.41);
    layout->addWidget(player,3);

    //Spinbox for frame jumps
    QSpinBox *frameSkip = new QSpinBox;
    frameSkip->setRange(1, 1000); //min skip is 1 frame, max skip is 1000frames
    frameSkip->setSingleStep(1); //1 frame per click
    frameSkip->setValue(0);

    QHBoxLayout *frameSkipGroup = new QHBoxLayout();
    QLabel *frameSkipLabel = new QLabel("Frameskip Rate (ms):");
    frameSkipGroup->addWidget(frameSkipLabel);
    frameSkipGroup->addWidget(frameSkip);

    east->addWidget(thePointTracker);
    east->addLayout(frameSkipGroup);

    layout->addLayout(east);

    mainLayout->addLayout(topRow, 3);
    mainLayout->addLayout(layout);

    connect(frameSkip, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int i){frameStep = i; /* ??? */ });

    QWidget* window = new QWidget();
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
void MainWindow::openHelpMenu()
{
    helpmenu.show();
}

void MainWindow::refreshPointTracker()
{
    thePointTracker->repaint();
}
