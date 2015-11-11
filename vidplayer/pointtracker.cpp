#include "pointtracker.h"
#include "ui_pointtracker.h"
#include <QDebug>

pointtracker::pointtracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pointtracker)
{
    ui->setupUi(this);
    QObject::connect(ui->objectList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listChanged()));
}

pointtracker::~pointtracker()
{
    delete ui;
}

void pointtracker::on_addObjectButton_clicked()
{
    QVector<point_t> points;
    points.push_back(point_t(itemLists.size(), 0, 0, 0));
//    point_t newPoint;
//    for (int i = 0; i < 5; ++i)
//    {
//        newPoint = QString("Test: " +  QString::number(i));
//        points.push_back(newPoint);
//    }
    itemLists.append(points);
    ui->objectList->addItem("Object " + QString::number(itemLists.size()));
    //Set newly made to index
    ui->objectList->setCurrentIndex(ui->objectList->count() - 1);
    updateList();
}

void pointtracker::on_deletePointButton_clicked()
{
    int index = ui->pointsList->currentRow();
    if (index >= 0) {
        itemLists[ui->objectList->currentIndex()].removeAt(index);
        updateList();
    }
}

void pointtracker::on_deleteObjectButton_clicked()
{
    int index = ui->objectList->currentIndex();
    if (index >= 0) {
        ui->objectList->removeItem(index);
        itemLists.removeAt(index);
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
    int index = ui->objectList->currentIndex();
    if (index >= 0) {
        for (point_t &item : itemLists[index])
        {
            ui->pointsList->addItem("ID: " + QString::number(item.ID) + " x: " + QString::number(item.x));
        }
    }
}
