#include "pointstruct.h"

point_t::point_t() {
    ID = -1;
    x = -1;
    y = -1;
    time = -1.0;
    isDiscontinuity = 0;
}

point_t::point_t(const int myID, const double myX, const double myY, const int t, const QColor c, int isDisc) {
    ID = myID;
    x = myX;
    y = myY;
    time = t;
    color = c;
    isDiscontinuity = isDisc;
}

int currentObjectIndex = 0;
int frameStep = 20; //Step 20 frames
QColor currentColor = Qt::blue;
//QVector<point_t> points;
QVector< QVector<point_t> > objectsListVec;
bool objectsListDirty = true;
int clickAction = 0;
int tZero = 0;
int lastSelected = -1;
QPoint origin = {0,0};
QVector<point_t> filterID(int id) {
    QVector<point_t> po;
    Q_FOREACH(point_t p, objectsListVec[currentObjectIndex]) {
        if (p.ID == id) {
            po.append(p);
        }
    }
    return po;
}
