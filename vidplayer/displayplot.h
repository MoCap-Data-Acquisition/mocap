#ifndef DISPLAYPLOT
#define DISPLAYPLOT
#include <QMainWindow>
#include "qcustomplot.h"

class NewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewWindow(QWidget *parent = 0);
    ~NewWindow();
    void setupPlot();
    void showSimplePlot(QCustomPlot *customPlot);
    QCustomPlot *customPlot;

private:
   // NewWindow *window;
    //QCustomPlot *customPlot;

};

#endif // DISPLAYPLOT

