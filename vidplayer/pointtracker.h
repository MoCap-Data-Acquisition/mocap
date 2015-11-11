#ifndef POINTTRACKER_H
#define POINTTRACKER_H

#include <QMainWindow>
#include <QStringListModel>
#include <QStringList>
#include <QAbstractItemView>
#include <QListWidgetItem>
#include <QVector>
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

private:
    Ui::pointtracker *ui;
    QStringListModel *model;
    QVector< QVector<point_t>> itemLists;
    void updateList();

};

#endif // POINTTRACKER_H
