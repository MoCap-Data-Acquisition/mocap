#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QVector>
#include <QtGui>
#include <QDebug>
#include "pointstruct.h"

class VideoWidget : public QGraphicsView
{
    Q_OBJECT

public:
    QVector<qint64>* xCoord = new QVector<qint64>;
    QVector<qint64>* yCoord = new QVector<qint64>;
    QVector<qint64>* tCoord = new QVector<qint64>;
    VideoWidget(QWidget *parent = 0);
    void setVideoPlayer(QMediaPlayer *player);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QGraphicsScene *scene;
    QGraphicsVideoItem *item;
    point_t drawPoint;
};

#endif // VIDEOWIDGET_H
