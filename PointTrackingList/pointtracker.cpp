#include "pointtracker.h"
#include "ui_pointtracker.h"



pointtracker::pointtracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pointtracker)
{
    ui->setupUi(this);

    //Data added
    //QStringList List;
    //List << "Test" << "Foo" << "Bar";
    itemLists = QVector<QVector<QListWidgetItem> >();
    for(int i = 0; i < 10; ++i)
    {
        ui->pointsList->addItem("Item " + QString::number(i));
    }
}

pointtracker::~pointtracker()
{
    delete ui;
}
void pointtracker::on_addObjectButton_clicked()
{
    testObjectCount += 1;
    QVector<QListWidgetItem> points = QVector<QListWidgetItem>();
    QListWidgetItem newPoint;
    for (int i = 0; i < 5; ++i)
    {
        newPoint = QListWidgetItem(("Test: " +  QString::number(i)));
        points.push_back(newPoint);
    }
    itemLists.append(points);
    ui->objectList->addItem("Object " + QString::number(testObjectCount));
    //Set newly made to index
    ui->objectList->setCurrentIndex(ui->objectList->count());
    updateList();
}
void pointtracker::on_deletePointButton_clicked()
{
    QListWidgetItem *item = ui->pointsList->currentItem();
    //QListWidgetItem testItem = *item;
    item->setText("Deleted");
    //int indexOfSelected = itemLists.at(ui->objectList->currentIndex()).indexOf(testItem);
    //itemLists.at(ui->objectList->currentIndex()).remove(indexOfSelected);
    qDebug() << "Item Removed";
    ui->pointsList->removeItemWidget(item);
    updateList();
}
void pointtracker::on_deleteObjectButton_clicked()
{
    ui->objectList->removeItem(ui->objectList->currentIndex());
    if(testObjectCount >= 0) {testObjectCount-=1;}
    updateList();
}

void pointtracker::updateList()
{
    ui->pointsList->clear();
    for (QListWidgetItem &item : itemLists[ui->objectList->currentIndex()])
    {
        ui->pointsList->addItem(&item);
    }
}

