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

    void on_pushButton_clicked();

private:
    int lastSelected;
    void paintEvent(QPaintEvent *event);
    Ui::pointtracker *ui;
    QStringListModel *model;
    QColor randomColorGenerator();
};

#endif // POINTTRACKER_H
