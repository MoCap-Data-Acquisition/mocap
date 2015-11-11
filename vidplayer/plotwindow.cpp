#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "mainwindow.h"
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

PlotWindow::PlotWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlotWindow)
{
    ui->setupUi(this);
    setGeometry(400, 250, 542, 390);
//    setupDisplayTest();
}
void PlotWindow::setupDisplayTest()
{
    setupSimpleDemo();
    setWindowTitle("Custom Plot Test");
    statusBar()->clearMessage();
    ui->customPlotX->replot();
    ui->customPlotY->replot();
}
void PlotWindow::setupSimpleDemo()
{

    std::unordered_set<int> ids;
    std::unordered_map<int, QVector<double> > xs;
    std::unordered_map<int, QVector<double> > ys;
    QVector<double> time;
    qDebug() << "points: " << points.size();
    for (point_t& p : points) {
        ids.emplace(p.ID);
        xs[p.ID].append(p.x);
        ys[p.ID].append(p.y);
        time.append(p.time);
     //   qDebug() << "yo";
    }
    for (int id : ids) {
        ui->customPlotX->addGraph();
        ui->customPlotY->addGraph();
        ui->customPlotX->graph(ui->customPlotX->graphCount()-1)->addData(time, xs[id]);
        ui->customPlotY->graph(ui->customPlotY->graphCount()-1)->addData(time, ys[id]);
    }



//    customPlot->graph(0)->setData(x, t);
    // give the axes some labels:
    ui->customPlotX->xAxis->setLabel("t");
    ui->customPlotX->yAxis->setLabel("x");
    ui->customPlotY->xAxis->setLabel("t");
    ui->customPlotY->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    double maxTime = *std::max_element(time.begin(),time.end());
    double maxX = std::numeric_limits<double>::min();
    double maxY = std::numeric_limits<double>::min();
    for (const std::pair<int, QVector<double> >& pair : xs) {
        maxX = std::max(*std::max_element(pair.second.begin(), pair.second.end()), maxX);
        maxY = std::max(*std::max_element(ys[pair.first].begin(), ys[pair.first].end()), maxY);
    }
    ui->customPlotX->xAxis->setRange(0, maxTime);
    ui->customPlotX->yAxis->setRange(0, 500);
    ui->customPlotY->xAxis->setRange(0, maxTime);
    ui->customPlotY->yAxis->setRange(0, 500);
    //customPlot->replot();
}

PlotWindow::~PlotWindow()
{
    delete ui;
}
