#include "pointtracker.h"
#include "ui_pointtracker.h"
#include <random>

pointtracker::pointtracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pointtracker)
{
    ui->setupUi(this);
    QObject::connect(ui->objectList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listChanged()));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    on_addObjectButton_clicked();
}

pointtracker::~pointtracker()
{
    delete ui;
}

void pointtracker::on_addObjectButton_clicked()
{
    QVector<point_t> newObject;
    objectsListVec.push_back(newObject);
    currentColor = randomColorGenerator();
    ui->objectList->addItem("Object " + QString::number(objectsListVec.size()));
    //Set newly made to index
    ui->objectList->setCurrentIndex(ui->objectList->count() - 1);
    repaint();
}

void pointtracker::on_deletePointButton_clicked()
{
    currentObjectIndex = ui->pointsList->currentRow();
    if (currentObjectIndex >= 0) {
        objectsListVec[ui->objectList->currentIndex()].removeAt(currentObjectIndex);
        repaint();
    }
}

void pointtracker::on_deleteObjectButton_clicked()
{
    currentObjectIndex = ui->objectList->currentIndex();
    if (currentObjectIndex >= 0) {
        ui->objectList->removeItem(currentObjectIndex);
        objectsListVec.removeAt(currentObjectIndex);
        repaint();
    }
}

void pointtracker::paintEvent(QPaintEvent *event)
{
    ui->pointsList->clear();
    currentObjectIndex = ui->objectList->currentIndex();
    if (objectsListVec[currentObjectIndex].length() > 0)
        currentColor = objectsListVec[currentObjectIndex][0].color;

    if (currentObjectIndex >= 0) {
        for (point_t &item : objectsListVec[currentObjectIndex])
        {
            ui->pointsList->addItem("ID: " + QString::number(item.ID) + " x: " + QString::number(item.x));
        }
    }
    QMainWindow::paintEvent(event);
}
QColor pointtracker::randomColorGenerator()
{
    std::default_random_engine rd((std::random_device())());
    std::uniform_int_distribution<int> gen(0,255);
    return QColor(gen(rd), gen(rd), gen(rd));
}
