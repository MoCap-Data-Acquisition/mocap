#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QVector>
#include <QtGui>
#include <QDebug>
#include <cmath>
#include "pointstruct.h"

#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVideo.h>

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    VideoWidget(QWidget *parent = 0);

public slots:
    void setRotateVideo(bool rotate);
    void exportCSVData();
    void toggleRotateVideo();
    void setMediaPlayer(VlcMediaPlayer *player);

protected:
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    //QGraphicsScene *scene;
    //QGraphicsProxyWidget *proxy;
    VlcWidgetVideo *video;
    point_t drawPoint;
    bool videoRotated;
    double calibrationRatio = -1.0;
    int isCalibrated = 0;
    QPoint p1;
};

#endif // VIDEOWIDGET_H
