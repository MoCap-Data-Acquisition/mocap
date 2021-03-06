/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <VLCQtCore/MediaPlayer.h>
#include <QImage>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSysInfo>

#include "GraphicsVlcItem.h"
#include <QDebug>

GraphicsVlcItem::GraphicsVlcItem(QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _player(nullptr),
      _boundingRect(0, 0, 0, 0),
      _videoRect(0, 0, 0, 0),
      _transform(),
      _drawn(true),
      _rot(false)
{  }

GraphicsVlcItem::~GraphicsVlcItem() {  }

// This allows _transform to be agnostic to the screen size
// by scaling the translation by _boundingRect
QTransform GraphicsVlcItem::prepared() {
    return QTransform(
                _transform.m11(), _transform.m12(), _transform.m13(),
                _transform.m21(), _transform.m22(), _transform.m23(),
                _transform.m31() * _boundingRect.width(),
                _transform.m32() * _boundingRect.height(),
                _transform.m33()
            );
}

void GraphicsVlcItem::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    _mutex.lock();
    painter->fillRect(_boundingRect, QBrush(Qt::black));
    if( _frame.inited )
    {
        QImage image(reinterpret_cast<const uchar *>(_frame.plane[0].constData()), _frame.width, _frame.height, QImage::Format_RGB32);
        painter->setTransform(prepared(), true);
        painter->drawImage(_videoRect, image);
    }
    _drawn = true;
    _mutex.unlock();
}

QRectF GraphicsVlcItem::boundingRect() const {
    return _boundingRect;
}

void GraphicsVlcItem::resize(const QSizeF &size) {
    _boundingRect.setSize(size);
    setVideoRect();
    prepareGeometryChange();
}

//Rotate Video 180 degrees
void GraphicsVlcItem::rotate180() {
    _transform *= QTransform(-1, 0, 0, -1, 1, 1);
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

//Rotate Video +90 degrees
void GraphicsVlcItem::rotateP(){
    _transform *= QTransform(0, 1, -1, 0, 1, 0);
    _rot = !_rot;
    setVideoRect();
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

//Rotate Video -90 degrees
void GraphicsVlcItem::rotateN(){
    _transform *= QTransform(0, -1, 1, 0, 0, 1);
    _rot = !_rot;
    setVideoRect();
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

//Mirror Video
void GraphicsVlcItem::mirror(){
    _transform *= QTransform(-1, 0, 0, 1, 1, 0);
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

void GraphicsVlcItem::frameReady()
{
    update();
}

void GraphicsVlcItem::reset()
{
    // Do not reset the spyFormats as they will not change.
    update();
}

void GraphicsVlcItem::setMediaPlayer(VlcMediaPlayer *player)
{
    if (_player == nullptr) {
        setCallbacks(player);
        _player = player;
    }
}

void GraphicsVlcItem::setVideoRect() {
    if (_frame.width > 0 && _frame.height > 0) {
        QSizeF wsize = _boundingRect.size();
        if (_rot) wsize = QSizeF(wsize.height(), wsize.width());
        QSizeF size = wsize;
        QPointF point(0, 0);
        qreal itemRatio = size.width() / size.height();
        qreal videoRatio = (qreal) _frame.width / _frame.height;
        if (itemRatio > videoRatio) {
            size.setWidth(size.height() * videoRatio);
            point.setX((wsize.width() - size.width()) / 2);
        } else if (itemRatio < videoRatio) {
            size.setHeight(size.width() / videoRatio);
            point.setY((wsize.height() - size.height()) / 2);
        }
        _videoRect = QRectF(point, size);
    }
}

void *GraphicsVlcItem::lockCallback(void **planes)
{
    _mutex.lock();

    for (unsigned int i = 0; i < _frame.planeCount; ++i) {
        planes[i] = reinterpret_cast<void *>(_frame.plane[i].data());
    }

    return 0; // There is only one buffer, so no need to identify it.
}

void GraphicsVlcItem::unlockCallback(void *picture, void *const*planes)
{
    _frame.inited = true;
    // To avoid thread polution do not call frameReady directly, but via the
    // event loop.
    if (_drawn) {
        QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
        _drawn = false;
    }
    _mutex.unlock();
    Q_UNUSED(picture);
    Q_UNUSED(planes);
}

void GraphicsVlcItem::displayCallback(void *picture)
{
    Q_UNUSED(picture); // There is only one buffer.
}

unsigned int GraphicsVlcItem::formatCallback(char *chroma,
                                                 unsigned *width, unsigned *height,
                                                 unsigned *pitches, unsigned *lines)
{
#if Q_BYTE_ORDER == Q_LITTLE_ENDIAN
    qstrcpy(chroma, "BGRA");
#else
    qstrcpy(chroma, "ARGB");
#endif

    _frame.width = *width;
    _frame.height = *height;
    _frame.planeCount = 1;

    setVideoRect();

    _frame.visiblePitch[0] = _frame.pitch[0] = pitches[0] = *width * 4;
    _frame.visibleLines[0] = _frame.lines[0] = lines[0] = *height;
    _frame.plane[0].resize(pitches[0] * lines[0]);

    return pitches[0] * lines[0];
}

void GraphicsVlcItem::formatCleanUpCallback()
{
    _frame.inited = false;
    _frame.width = 0;
    _frame.height = 0;
    // To avoid thread polution do not call reset directly but via the event loop.
    QMetaObject::invokeMethod(this, "reset", Qt::QueuedConnection);
}
