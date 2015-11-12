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
    VideoWidget(QWidget *parent = 0);
    void setVideoPlayer(QMediaPlayer *player);

public slots:
    void setRotateVideo(bool rotate);
    void toggleRotateVideo();

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QGraphicsScene *scene;
    QGraphicsVideoItem *item;
    point_t drawPoint;
    bool videoRotated;
};

#endif // VIDEOWIDGET_H
