#ifndef PLAYER_H
#define PLAYER_H

#include "videowidget.h"

#include <QWidget>

#include <VLCQtCore/Enums.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetSeek.h>

class QAbstractItemView;
class QLabel;
class QMediaPlayer;
class QModelIndex;
class QPushButton;
class QSlider;
class QVideoProbe;
class QVideoWidget;

class PlaylistModel;
class HistogramWidget;

class Player : public QWidget
{
    Q_OBJECT

public:
    Player(QWidget *parent = 0);
    ~Player();
    VideoWidget *videoWidget;

public slots:
    void frameUp();
    void frameDown();
    Vlc::State getPlayerState();
    float currentPosition();
    int currentTime();
    int currentLength();

signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    void open();

    void previousClicked();
    void timeChanged(int time);

    void jump(const QModelIndex &index);

    void statusChanged(Vlc::State status);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();

private:
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(Vlc::State status);
    void updateDurationInfo(qint64 currentInfo);

    QLabel *coverLabel;
    QLabel *labelDuration;
    QPushButton *nextFrame;
    QPushButton *prevFrame;

    VlcInstance *vlc;
    VlcMediaPlayer *player;
    VlcWidgetSeek *slider;

    QString trackInfo;
    QString statusInfo;
    qint64 duration;
};

#endif // PLAYER_H
