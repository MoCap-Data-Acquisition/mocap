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

GraphicsVlcItem::GraphicsVlcItem(QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _player(nullptr),
      _boundingRect(0, 0, 0, 0),
      _videoRect(0, 0, 0, 0),
      _drawn(true)
{  }

GraphicsVlcItem::~GraphicsVlcItem() {  }

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
        QImage image((const uchar *) _frame.plane[0].constData(), _frame.width, _frame.height, _frame.pitch[0], QImage::Format_RGB32);
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
        QSizeF size = _boundingRect.size();
        QPointF point(0, 0);
        qreal itemRatio = size.width() / size.height();
        qreal videoRatio = (qreal) _frame.width / _frame.height;
        if (itemRatio > videoRatio) {
            size.setWidth(size.height() * videoRatio);
            point.setX((_boundingRect.width() - size.width()) / 2);
        } else if (itemRatio < videoRatio) {
            size.setHeight(size.width() / videoRatio);
            point.setY((_boundingRect.height() - size.height()) / 2);
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

#include <QDebug>
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
