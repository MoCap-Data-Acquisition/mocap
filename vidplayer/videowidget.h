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

    void paintEvent(QPaintEvent *event)
    {
        qDebug() << Q_FUNC_INFO;
        QPainter painter(this);
        //painter.setPen(Qt::SolidLine);
        Q_FOREACH(point_t point, points) {
            qDebug() << "Drawing Point: (" << point.x << ", " << point.y << ")";
            painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
            painter.drawEllipse(point.x, point.y, 2, 2);
        }
    }
};

#endif // VIDEOWIDGET_H
