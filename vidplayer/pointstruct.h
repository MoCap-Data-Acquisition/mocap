#ifndef POINT_STRUCT
#define POINT_STRUCT

#include <QColor>
#include <QVector>


struct point_t 
{
   int ID;
   double x;
   double y;
   int time;
   QColor color;

   point_t();
   point_t(const int myID, const double myX, const double myY, const int t, const QColor c = Qt::blue);
};

extern QVector<point_t> points;

QVector<point_t> filterID(int id);

#endif
