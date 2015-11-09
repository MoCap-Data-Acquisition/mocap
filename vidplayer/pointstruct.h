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

   point_t(const int myID, const int myX, const int myY, const double t, const QColor c) {
       myID = ID;
       myX = x;
       myY = y;
       t = time;
       c = color;
   }
};

QVector<point_t> points;

QVector<const point_t&> filterID(int id) {
   QVector<point_t> po();
   for (auto& p : points) {
       if (p.myID == id) {
           po.append(p);
       }
   }
}


#endif
