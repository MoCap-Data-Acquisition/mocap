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

#ifndef VLCQT_QMLVIDEOOBJECT_H_
#define VLCQT_QMLVIDEOOBJECT_H_

#include <QMutex>
#include <QGraphicsItem>
#include <QWaitCondition>

#include <VLCQtCore/Enums.h>
#include <VLCQtCore/VideoFrame.h>
#include <VLCQtCore/VideoMemoryStream.h>

class VlcMediaPlayer;

/*!
    \class VlcQmlVideoObject QmlVideoObject.h VLCQtQml/QmlVideoObject.h
    \ingroup VLCQtQml
    \brief QML video object

    A basic QML video object for painting video. It acts as a replacement for video widget.
 */
class GraphicsVlcItem : public QGraphicsObject,
                        public VlcVideoMemoryStream
{
Q_OBJECT
public:
    /*!
        \brief VlcQmlVideoObject constructor.
        \param parent parent item
     */
    explicit GraphicsVlcItem(QGraphicsItem *parent = nullptr);

    /*!
        VlcMediaPlayer destructor
     */
    virtual ~GraphicsVlcItem();

    virtual QRectF boundingRect() const override;

    void resize(const QSizeF & size);

    /*!
        \brief Connect to media player
        \param player media player
     */
    void setMediaPlayer(VlcMediaPlayer *player);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = nullptr) override;

protected:
    /*!
        \brief Core media player
     */
    VlcMediaPlayer *_player;

private slots:
    void frameReady();
    void reset();

private:
    void setVideoRect();

    virtual void *lockCallback(void **planes) override;
    virtual void unlockCallback(void *picture, void *const *planes) override;
    virtual void displayCallback(void *picture) override;

    virtual unsigned formatCallback(char *chroma,
                                    unsigned *width, unsigned *height,
                                    unsigned *pitches,
                                    unsigned *lines) override;
    virtual void formatCleanUpCallback() override;

    QMutex _mutex;
    VlcVideoFrame _frame;
    QRectF _boundingRect, _videoRect;
    bool _drawn;
};

#endif // VLCQT_QMLVIDEOOBJECT_H_
