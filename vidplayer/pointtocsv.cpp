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
#include <QTextStream>
#include <QtGlobal>

bool writePointsToCSV(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) return false;
    QTextStream out(&file);
    out << "\"ID\", \"x\", \"y\", \"time\", \"isDiscontinuity?\"\n";
    for (int i = 0; i < objectsListVec.size(); ++i)
    {
        Q_FOREACH(point_t p, objectsListVec[i]) {
            out << p.ID << ", " << p.x << ", " << p.y << ", " << p.time << ", " << p.isDiscontinuity << "\n";
        }
    }
    file.close();
    return true;
}
