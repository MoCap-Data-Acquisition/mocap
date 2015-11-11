#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QVideoWidget>
#include <QVector>
#include <QtGui>
#include <QDebug>
#include "pointstruct.h"

class VideoWidget : public QVideoWidget
{
    Q_OBJECT

public:
    QVector<qint64>* xCoord = new QVector<qint64>;
    QVector<qint64>* yCoord = new QVector<qint64>;
    QVector<qint64>* tCoord = new QVector<qint64>;
    VideoWidget(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_H
