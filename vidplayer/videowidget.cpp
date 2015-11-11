
#include "videowidget.h"
#include "player.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <iostream>

#include "pointstruct.h"


VideoWidget::VideoWidget(QWidget *parent)
    : QVideoWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen()) {
        setFullScreen(false);
        event->accept();
    } else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt) {
        setFullScreen(!isFullScreen());
        event->accept();
    } else {
        QVideoWidget::keyPressEvent(event);
    }
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    /*setFullScreen(!isfullscreen());
    event->accept();*/
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    //xCoord->append(event->x());
    //customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for firsyCoord->append(event->y());
   // tCoord->append(((Player*)parentWidget())->timeinMillis);
    auto time = ((Player*)parentWidget())->timeinMillis;
    point_t myPoint(0, event->x(), event->y(), time);
    qDebug() << "Point Added: (" << QString::number((int)event->x()) << ", " << QString::number((int) event->y()) << ", " << QString::number(time) << ")";
    points.push_back(myPoint);
    QVideoWidget::mousePressEvent(event);
    update();
}
