#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotwindow.h"
#include "player.h"
#include "pointtracker.h"
#include "help.h"

#include "optionsmenu.h"

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
    void openOptionsMenu();
    void refreshPointTracker();
private:
    Player* player;
    pointtracker* thePointTracker;

    Ui::MainWindow *ui;
   // NewWindow *displayPlotWindow;
    PlotWindow displayPlotWindow;
    Help helpmenu;
    OptionsMenu options;

};

#endif // MAINWINDOW_H
