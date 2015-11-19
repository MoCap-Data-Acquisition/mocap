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
   int isDiscontinuity;

   point_t();
   point_t(const int myID, const double myX, const double myY, const int t, const QColor c, int isDisc);
};

//extern QVector<point_t> points;
extern QVector< QVector<point_t>> objectsListVec;
extern bool objectsListDirty;
extern QColor currentColor;
QVector<point_t> filterID(int id);
extern int currentObjectIndex; //current object

#endif
