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
    explicit PlotWindow(QWidget *parent = 0);
    ~PlotWindow();
    void setupDisplayTest();
    void setupSimpleDemo();

private:
    Ui::PlotWindow *ui;
};

#endif // PLOTWINDOW_H
