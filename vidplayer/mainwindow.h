#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotwindow.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void openDisplayPlot();
private:
    Ui::MainWindow *ui;
   // NewWindow *displayPlotWindow;
    PlotWindow *displayPlotWindow;
};

#endif // MAINWINDOW_H
