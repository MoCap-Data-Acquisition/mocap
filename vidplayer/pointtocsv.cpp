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
    int discCounter=0;
    out << "\"ID\", \"x\", \"y\", \"time\", \"isDiscontinuity?\"\n";
    for (int i = 0; i < objectsListVec.size(); ++i)
    {
        Q_FOREACH(point_t p, objectsListVec[i]) {
            if(p.isDiscontinuity == 1){
                discCounter += 1;
                out << p.ID << ", " << p.x << ", " << p.y << ", " << p.time << ", " << (p.isDiscontinuity + discCounter - 1) << "\n";
                out << p.ID << ", " << p.x << ", " << p.y << ", " << p.time << ", " << (p.isDiscontinuity + discCounter - 1) << "\n";
            }
            out << p.ID << ", " << p.x << ", " << p.y << ", " << p.time << ", " << discCounter << "\n";
        }
        discCounter = 0;
    }
    file.close();
    return true;
}
