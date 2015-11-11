
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
    xCoord->append(event->x());
    yCoord->append(event->y());
    tCoord->append(((Player*)parentWidget())->timeinMillis);
    QVideoWidget::mousePressEvent(event);
    update();
}
