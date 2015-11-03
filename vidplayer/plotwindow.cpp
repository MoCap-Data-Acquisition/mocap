#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "mainwindow.h"

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    setupDisplayTest();
}
void PlotWindow::setupDisplayTest()
{
    setupSimpleDemo(ui->customPlot);
    setWindowTitle("Custom Plot Test");
    statusBar()->clearMessage();
    ui->customPlot->replot();
}
void PlotWindow::setupSimpleDemo(QCustomPlot *customPlot)
{
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    //customPlot->replot();
}

PlotWindow::~PlotWindow()
{
    delete ui;
}
