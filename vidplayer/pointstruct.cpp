#include "pointstruct.h"

point_t::point_t() {
    ID = -1;
    x = -1;
    y = -1;
    time = -1.0;
}

point_t::point_t(const int myID, const double myX, const double myY, const int t, const QColor c) {
    ID = myID;
    x = myX;
    y = myY;
    time = t;
    color = c;
}

int currentObjectIndex = 0;
QColor currentColor = Qt::blue;
//QVector<point_t> points;
QVector< QVector<point_t> > objectsListVec;
bool objectsListDirty = true;

QVector<point_t> filterID(int id) {
    QVector<point_t> po;
    Q_FOREACH(point_t p, objectsListVec[currentObjectIndex]) {
        if (p.ID == id) {
            po.append(p);
        }
    }
    return po;
}
