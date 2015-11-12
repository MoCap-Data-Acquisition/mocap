#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QMediaPlayer>
#include <QVector>
#include <QtGui>
#include <QDebug>
#include <cmath>
#include "pointstruct.h"

class VideoWidget : public QGraphicsView
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0);
    void setVideoPlayer(QMediaPlayer *player);

public slots:
    void setRotateVideo(bool rotate);
    void exportCSVData();
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
    double calibrationRatio = -1.0;
    int isCalibrated = 0;
    QPoint p1;
};

#endif // VIDEOWIDGET_H
