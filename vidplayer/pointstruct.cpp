#include "pointstruct.h"

point_t::point_t() {
    ID = -1;
    x = -1;
    y = -1;
    time = -1.0;
}

point_t::point_t(const int myID, const int myX, const int myY, const double t, const QColor c) {
    ID = myID;
    x = myX;
    y = myY;
    time = t;
    color = c;
}

QVector<point_t> points;

QVector<point_t> filterID(int id) {
    QVector<point_t> po;
    Q_FOREACH(point_t p, points) {
        if (p.ID == id) {
            po.append(p);
        }
    }
    return po;
}
