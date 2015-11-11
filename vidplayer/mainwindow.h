#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotwindow.h"
#include "player.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//protected:
//    void keyPressEvent(QKeyEvent *event);

public slots:
    void openDisplayPlot();
private:
    Player* player;
    Ui::MainWindow *ui;
   // NewWindow *displayPlotWindow;
    PlotWindow displayPlotWindow;
};

#endif // MAINWINDOW_H
