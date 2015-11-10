#include "pointtracker.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pointtracker w;
    w.show();

    return a.exec();
}
