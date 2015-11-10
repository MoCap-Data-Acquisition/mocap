#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "mainwindow.h"

PlotWindow::PlotWindow(const QVector<qint64> &t, const QVector<qint64> &x, const QVector<qint64> &y, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
    setupDisplayTest(t,x,y);
}
void PlotWindow::setupDisplayTest(const QVector<qint64> &t, const QVector<qint64> &x, const QVector<qint64> &y)
{
    setupSimpleDemo(ui->customPlotX, t, x);
    setupSimpleDemo(ui->customPlotY, t, y);
    setWindowTitle("Custom Plot Test");
    statusBar()->clearMessage();
    ui->customPlotX->replot();
    ui->customPlotY->replot();
}
void PlotWindow::setupSimpleDemo(QCustomPlot *customPlot, const QVector<qint64> &v1, const QVector<qint64> &v2)
{
    // generate some data:
//    QVector<double> x(101), y(101); // initialize with entries 0..100
//    for (int i=0; i<101; ++i)
//    {
//      x[i] = i/50.0 - 1; // x goes from -1 to 1
//      y[i] = x[i]*x[i]; // let's plot a quadratic function
//    }
    // create graph and assign data to it:
    customPlot->addGraph();
    QVector<double> v1d(v1.length()), v2d(v2.length());
    for (int i = 0; i < v1.length(); ++i) {
        v1d[i] = v1[i];
        v2d[i] = v2[i];
    }
    customPlot->graph(0)->setData(v1d, v2d);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(0, 500);
    customPlot->yAxis->setRange(0, 500);
    //customPlot->replot();
}

PlotWindow::~PlotWindow()
{
    delete ui;
}
