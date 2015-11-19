#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotwindow.h"
#include "player.h"
#include "pointtracker.h"
#include "helpmenu.h"

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
    void openHelpMenu();
    void refreshPointTracker();
private:
    Player* player;
    pointtracker* thePointTracker;

    Ui::MainWindow *ui;
   // NewWindow *displayPlotWindow;
    PlotWindow displayPlotWindow;
    Helpmenu helpmenu;

};

#endif // MAINWINDOW_H
