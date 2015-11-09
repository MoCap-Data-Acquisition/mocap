//
//  pointtocsv.cpp
//  
//
//  Created by Lewis Fox on 11/8/15.
//
//

#include "pointtocsv.h"
#include "pointstruct.h"

#include <QFile>
#include <QDataStream>
#include <QtGlobal>

bool writePointsToCSV(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) return false;
    QDataStream out(&file);
    out << "\"ID\", \"x\", \"y\", \"time\"\n";
    Q_FOREACH(point_t p, points) {
        out << p.ID << ", " << p.x << ", " << p.y << ", " << p.time << "\n";
    }
    file.close();
    return true;
}
