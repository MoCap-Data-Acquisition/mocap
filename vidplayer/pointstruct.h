#ifndef POINT_STRUCT
#define POINT_STRUCT

#include <QColor>
#include <QVector>


struct point_t 
{
   int ID;
   int x;
   int y;
   double time;
   QColor color;

   point_t();
   point_t(const int myID, const int myX, const int myY, const double t, const QColor c);
};

extern QVector<point_t> points;

QVector<point_t> filterID(int id);

#endif
