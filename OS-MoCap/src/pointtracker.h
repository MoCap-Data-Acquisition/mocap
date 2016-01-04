#ifndef POINTTRACKER_H
#define POINTTRACKER_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QVector>
#include <QPaintEvent>
#include <QString>
#include <QDebug>
#include <QList>
#include "pointstruct.h"
namespace Ui {
class pointtracker;
}

class pointtracker : public QMainWindow
{
    Q_OBJECT

public:
    explicit pointtracker(QWidget *parent = 0);
    ~pointtracker();


private slots:
    void on_addObjectButton_clicked();
    void on_deletePointButton_clicked();
    void on_deleteObjectButton_clicked();
    void on_listChanged();

    void on_pointsList_itemClicked(QListWidgetItem *item);

    void on_markDiscontinuityBtn_clicked();

    void on_setScaleBtn_clicked();

    void on_setOriginBtn_clicked();

    void on_addPointsBtn_clicked();

private:
    void paintEvent(QPaintEvent *event);
    Ui::pointtracker *ui;
    QStringListModel *model;
    QColor randomColorGenerator();
    //QColor colorsList[];
    int theCurrentColor;
    point_t highlightpoint;


};

#endif // POINTTRACKER_H
