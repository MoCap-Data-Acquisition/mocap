
#include "videowidget.h"
#include "player.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>


VideoWidget::VideoWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));

    scene = new QGraphicsScene(this);
    item = new QGraphicsVideoItem();
    this->setScene(scene);
    scene->addItem(item);
}

void VideoWidget::setVideoPlayer(QMediaPlayer *player)
{
    player->setVideoOutput(item);
}

void VideoWidget::setRotateVideo(bool rotate) {
    QSizeF isize = item->size();
    item->setTransformOriginPoint(isize.width() / 2, isize.height() / 2);
    item->setRotation(rotate ? 180 : 0);
    videoRotated = rotate;
    scene->update();
}

void VideoWidget::toggleRotateVideo() {
    setRotateVideo(!videoRotated);
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    /*setFullScreen(!isfullscreen());
    event->accept();*/
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    auto time = ((Player*)parentWidget())->timeinMillis;
    point_t myPoint(currentObjectIndex, event->x(), event->y(), time, currentColor);
    qDebug() << "Point Added: (" << QString::number((int)event->x()) << ", " << QString::number((int) event->y()) << ", " << QString::number(time) << ")";
    objectsListVec[currentObjectIndex].push_back(myPoint);
    drawPoint = myPoint;
    QGraphicsView::mousePressEvent(event);
    scene->update();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    if (drawPoint.ID >= 0) {
        QPainter painter(this->viewport());
        painter.setBrush(QBrush(drawPoint.color, Qt::SolidPattern));
        painter.drawEllipse(drawPoint.x - 5, drawPoint.y - 5, 10, 10);
    }
}
