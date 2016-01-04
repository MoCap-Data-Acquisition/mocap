#include "pointtracker.h"
#include "ui_pointtracker.h"
#include <random>
#include <QMessageBox>
#include <QDebug>



QColor colorsList[] = {QColor(186,246,135,255), QColor(105,101,126,255), QColor(219,91,226,255), QColor(117,112,93,255), QColor(164,45,107,255),
                       QColor(123,237,243,255), QColor(176,75,35,255), QColor(0,0,255,255), QColor(0,255,0,255), QColor(215, 220, 219,255)};
pointtracker::pointtracker(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::pointtracker)
{
    ui->setupUi(this);
    QObject::connect(ui->objectList, SIGNAL(currentIndexChanged(int)), this, SLOT(on_listChanged()));
    connect(ui->pointsList, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(on_pointsList_itemClicked(QListWidgetItem*)));
    connect(ui->pointsList, SIGNAL(currentRowChanged(int)), this, SLOT(on_pointsList_currentRowChanged(int)));
    connect(ui->markDiscontinuityBtn, SIGNAL(clicked()), this, SLOT(on_markDiscontinuityBtn_clicked()));
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    on_addObjectButton_clicked();
    lastSelected = -1;
    ui->addPointsBtn->setEnabled(false);
    theCurrentColor = 0;
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
    //currentColor = randomColorGenerator();
    qDebug() << "Objects List Size: " << QString::number(objectsListVec.size());
    if(theCurrentColor < 9 && objectsListVec.size() != 1 ) theCurrentColor++;
    else theCurrentColor = 0;
    qDebug() << "Current Color: " << QString::number(theCurrentColor);
    currentColor = colorsList[theCurrentColor];
    ui->objectList->addItem("Trajectory " + QString::number(objectsListVec.size()));
    //Set newly made to index
    ui->objectList->setCurrentIndex(ui->objectList->count() - 1);
    repaint();
}

void pointtracker::on_deletePointButton_clicked()
{
    qDebug() << "pointsList size: " << QString::number(objectsListVec[currentObjectIndex].size());
        //currentObjectIndex = ui->pointsList->currentRow();

        if (lastSelected == -1){
            objectsListDirty = true;
            repaint();
        } //Do nothing
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
    qDebug() << "Last Selected: " << QString::number(lastSelected);
}

void pointtracker::on_deleteObjectButton_clicked()
{
    currentObjectIndex = ui->objectList->currentIndex();
    if (currentObjectIndex >= 0 && objectsListVec.size() > 1) {
        QMessageBox::StandardButton response;
        response = QMessageBox::question(this, "Delete Trajectory?", "Do you really want to delete this Trajectory?",
                                         QMessageBox::Yes | QMessageBox::No);
        if (response == QMessageBox::Yes) {
            qDebug() << "User has confirmed the deletion of Trajectory " << QString::number(currentObjectIndex) << " of Trajectories " << QString::number(objectsListVec.size());

                theCurrentColor--;
                if(theCurrentColor == -1) theCurrentColor = 0;
                ui->objectList->removeItem(currentObjectIndex);
                //objectsListVec[currentObjectIndex].clear();
               // objectsListVec.remove(currentObjectIndex);
                //qDebug() << "Removing objectListVec Index: " << QString::number(objectsListVec.indexOf(objectsListVec[currentObjectIndex]));
                objectsListVec.removeAt(currentObjectIndex + 1);
                objectsListDirty = true;
                repaint();
        } else {
            qDebug() << "The User does not want the Trajectory Deleted.";
        }
    }
}
void pointtracker::on_listChanged()
{
    objectsListDirty = true;
    repaint();
    lastSelected = -1;
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
                ui->pointsList->addItem("x: " + QString::number(item.x, 'f', 2) + " y: " + QString::number(item.y, 'f', 2) + " t: " + QString::number(item.time) + " ms" + (item.isDiscontinuity ? "  [Discontinuity]" : ""));
            }
        }
        if(lastSelected >= 0 && lastSelected != objectsListVec[currentObjectIndex].size())
            ui->pointsList->item(lastSelected)->setSelected(true); //Fixes bug where click items auto-unhighlight
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
    lastSelected = ui->pointsList->currentRow();
    objectsListDirty = true;
    update();
    Q_UNUSED(item);
}

void pointtracker::on_markDiscontinuityBtn_clicked()
{
    qDebug() << "Last Selected Marked as Discontinuity: " << QString::number(lastSelected);
    if (lastSelected >= 0) {
        if (objectsListVec[ui->objectList->currentIndex()][lastSelected].isDiscontinuity == 0) {
            objectsListVec[ui->objectList->currentIndex()][lastSelected].isDiscontinuity = 1;
            auto item = objectsListVec[ui->objectList->currentIndex()][lastSelected];
            on_listChanged();
            objectsListDirty = true;
            update();
        } else {
            objectsListVec[ui->objectList->currentIndex()][lastSelected].isDiscontinuity = 0;
            objectsListDirty = true;
            update();
        }
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
