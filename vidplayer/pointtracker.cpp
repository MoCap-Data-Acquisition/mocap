#include "pointtracker.h"
#include "ui_pointtracker.h"
#include <QDebug>

pointtracker::pointtracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pointtracker)
{
    ui->setupUi(this);
    QObject::connect(ui->objectList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listChanged()));
    on_addObjectButton_clicked();
}

pointtracker::~pointtracker()
{
    delete ui;
}

void pointtracker::on_addObjectButton_clicked()
{
    QVector<point_t> newObject;
    //newObject.push_back(point_t(objects.size(), 0, 0, 0));
//    point_t newPoint;
//    for (int i = 0; i < 5; ++i)
//    {
//        newPoint = QString("Test: " +  QString::number(i));
//        points.push_back(newPoint);
//    }
    objectsListVec.push_back(newObject);
    ui->objectList->addItem("Object " + QString::number(objectsListVec.size()));
    //Set newly made to index
    ui->objectList->setCurrentIndex(ui->objectList->count() - 1);
    updateList();
}

void pointtracker::on_deletePointButton_clicked()
{
    currentObjectIndex = ui->pointsList->currentRow();
    if (currentObjectIndex >= 0) {
        objectsListVec[ui->objectList->currentIndex()].removeAt(currentObjectIndex);
        updateList();
    }
}

void pointtracker::on_deleteObjectButton_clicked()
{
    currentObjectIndex = ui->objectList->currentIndex();
    if (index >= 0) {
        ui->objectList->removeItem(currentObjectIndex);
        objectsListVec.removeAt(currentObjectIndex);
        updateList();
    }
}

void pointtracker::on_listChanged()
{
    updateList();
}

void pointtracker::updateList()
{
    ui->pointsList->clear();
    currentObjectIndex = ui->objectList->currentIndex();
    if (currentObjectIndex >= 0) {
        for (point_t &item : objectsListVec[currentObjectIndex])
        {
            ui->pointsList->addItem("ID: " + QString::number(item.ID) + " x: " + QString::number(item.x));
        }
    }
}
