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
    void showSimplePlot(QCustomPlot *customPlot);
private:


};

#endif // DISPLAYPLOT

