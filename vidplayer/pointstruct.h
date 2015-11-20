#ifndef POINT_STRUCT
#define POINT_STRUCT

#include <QColor>
#include <QVector>
#include <QPoint>


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
extern int currentObjectIndex; //current Trajectory
extern int clickAction; //Determines what action a mouseclick will do: {nothing, set scale mode, set origin mode, point placement mode}
extern QPoint origin;
extern int tZero;
extern int frameStep;
#endif
