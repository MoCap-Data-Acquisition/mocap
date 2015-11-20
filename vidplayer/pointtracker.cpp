#include "pointtracker.h"
#include "ui_pointtracker.h"
#include <random>


pointtracker::pointtracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pointtracker)
{
    ui->setupUi(this);
    QObject::connect(ui->objectList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listChanged()));
    connect(ui->pointsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_pointsList_itemClicked(QListWidgetItem*)));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    on_addObjectButton_clicked();
    lastSelected = -1;
    ui->addPointsBtn->setEnabled(false);
}

pointtracker::~pointtracker()
{
    delete ui;
}

void pointtracker::on_addObjectButton_clicked()
{
    QVector<point_t> newObject;
    objectsListVec.push_back(newObject);
    objectsListDirty = true;
    currentColor = randomColorGenerator();
    ui->objectList->addItem("Trajectory " + QString::number(objectsListVec.size()));
    //Set newly made to index
    ui->objectList->setCurrentIndex(ui->objectList->count() - 1);
    repaint();
}

void pointtracker::on_deletePointButton_clicked()
{
    //currentObjectIndex = ui->pointsList->currentRow();
    if (lastSelected >= 0) {
        objectsListVec[ui->objectList->currentIndex()].removeAt(lastSelected);
        objectsListDirty = true;
        repaint();
    }
    if(lastSelected >= objectsListVec[currentObjectIndex].size()) {
        lastSelected = -1;
        objectsListDirty = true;
        repaint();
    }
}

void pointtracker::on_deleteObjectButton_clicked()
{
    currentObjectIndex = ui->objectList->currentIndex();
    if (currentObjectIndex >= 0 && objectsListVec.size() > 1) {
        ui->objectList->removeItem(currentObjectIndex);
        objectsListVec.removeAt(currentObjectIndex);
        objectsListDirty = true;
        repaint();
    }
}
void pointtracker::on_listChanged()
{
    objectsListDirty = true;
    repaint();
}
void pointtracker::paintEvent(QPaintEvent *event)
{
    if (objectsListDirty) {
        ui->pointsList->clear();
        currentObjectIndex = ui->objectList->currentIndex();
        if (objectsListVec[currentObjectIndex].length() > 0)
            currentColor = objectsListVec[currentObjectIndex][0].color;

        if (currentObjectIndex >= 0) {
            for (point_t &item : objectsListVec[currentObjectIndex])
            {
                ui->pointsList->addItem("x: " + QString::number(item.x, 'f', 2) + " y: " + QString::number(item.y, 'f', 2) + " t: " + QString::number(item.time) + " ms");
            }
        }
        objectsListDirty = false;
    }
    QMainWindow::paintEvent(event);
}
QColor pointtracker::randomColorGenerator()
{
    std::default_random_engine rd((std::random_device())());
    std::uniform_int_distribution<int> gen(0,255);
    return QColor(gen(rd), gen(rd), gen(rd));
}

void pointtracker::on_pointsList_itemClicked(QListWidgetItem *item)
{
    Q_UNUSED(item);
    lastSelected = ui->pointsList->currentRow();
    qDebug() << "Last item selected: " << QString::number(lastSelected);
}

void pointtracker::on_pushButton_clicked()
{

    if (lastSelected >= 0 && objectsListVec[ui->objectList->currentIndex()][lastSelected].isDiscontinuity == 0) {
        objectsListVec[ui->objectList->currentIndex()][lastSelected].isDiscontinuity = 1;
        auto item = objectsListVec[ui->objectList->currentIndex()][lastSelected];
        ui->pointsList->item(lastSelected)->setText("x: " + QString::number(item.x, 'f', 2) + " y: " + QString::number(item.y, 'f', 2) + " t: " + QString::number(item.time) + " ms" + "  [Discontinuity]");
        on_listChanged();
        objectsListDirty = true;
        repaint();
    } else {
        objectsListVec[ui->objectList->currentIndex()][lastSelected].isDiscontinuity = 0;
        objectsListDirty = true;
        repaint();
    }
}

void pointtracker::on_setScaleBtn_clicked()
{
    clickAction = 1;
    //->setEnabled(false);
    ui->setScaleBtn->setEnabled(false);
    ui->addPointsBtn->setEnabled(true);
}

void pointtracker::on_setOriginBtn_clicked()
{
    clickAction = 2;
    ui->setOriginBtn->setEnabled(false);
}

void pointtracker::on_addPointsBtn_clicked()
{
    ui->setOriginBtn->setEnabled(false); //fixes a bug.
    clickAction = 3;
}
