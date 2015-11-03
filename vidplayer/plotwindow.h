#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class PlotWindow;
}

class PlotWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlotWindow(const QVector<qint64> &t, const QVector<qint64> &x, const QVector<qint64> &y, QWidget *parent = 0);
    ~PlotWindow();
    void setupDisplayTest(const QVector<qint64> &t, const QVector<qint64> &x, const QVector<qint64> &y);
    void setupSimpleDemo(QCustomPlot *customPlot, const QVector<qint64> &v1, const QVector<qint64> &v2);

private:
    Ui::PlotWindow *ui;
};

#endif // PLOTWINDOW_H
