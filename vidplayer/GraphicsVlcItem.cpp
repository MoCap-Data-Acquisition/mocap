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
#include <QImage.h>
#include <QPainter.h>
#include <QGraphicsScene.h>
#include <QGraphicsView.h>
#include <QDebug.h>

#include "GraphicsVlcItem.h"

GraphicsVlcItem::GraphicsVlcItem(QGraphicsItem *parent)
    : QGraphicsObject(parent),
      _player(nullptr),
      _boundingRect(0, 0, 1280, 720)
{
    //setRenderTarget(InvertedYFramebufferObject);
    //setFlag(ItemHasContents, true);
}

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
        painter->drawImage(_boundingRect, image);
    }
    _mutex.unlock();
}

QRectF GraphicsVlcItem::boundingRect() const {
    return _boundingRect;
}

void GraphicsVlcItem::frameReady()
{
    update();
}

void GraphicsVlcItem::reset()
{
    // Do not reset the spyFormats as they will not change.
}

void GraphicsVlcItem::setMediaPlayer(VlcMediaPlayer *player)
{
    if (_player == nullptr) {
        setCallbacks(player);
        _player = player;
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
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    _mutex.unlock();
    // To avoid thread polution do not call frameReady directly, but via the
    // event loop.
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

void GraphicsVlcItem::displayCallback(void *picture)
{
    _frame.inited = true;
    Q_UNUSED(picture); // There is only one buffer.
}

unsigned int GraphicsVlcItem::formatCallback(char *chroma,
                                                 unsigned *width, unsigned *height,
                                                 unsigned *pitches, unsigned *lines)
{
    qstrcpy(chroma, "BGRA");

    _frame.width = *width;
    _frame.height = *height;
    _frame.planeCount = 1;

    _frame.visiblePitch[0] = _frame.pitch[0] = pitches[0] = *width * 4;
    _frame.visibleLines[0] = _frame.lines[0] = lines[0] = *height;
    _frame.plane[0].resize(pitches[0] * lines[0]);

    return pitches[0] * lines[0];
}

void GraphicsVlcItem::formatCleanUpCallback()
{
    _frame.inited = false;
    // To avoid thread polution do not call reset directly but via the event loop.
    QMetaObject::invokeMethod(this, "reset", Qt::QueuedConnection);
}
