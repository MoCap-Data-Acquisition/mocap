#ifndef PLAYER_H
#define PLAYER_H

#include "videowidget.h"

#include <QWidget>
#include <QVideoFrame>

#include <VLCQtCore/Instance.h>
#include <VLCQtCore/MediaPlayer.h>

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
    qint64 timeinMillis;
    ~Player();
    VideoWidget *videoWidget;

public slots:
    void frameUp();
    void frameDown();
    //void openDisplayPlot();
signals:
    void fullScreenChanged(bool fullScreen);

private slots:
    void open();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);

    void previousClicked();

    void seek(int seconds);
    void jump(const QModelIndex &index);

    void statusChanged(QMediaPlayer::MediaStatus status);
    void bufferingProgress(int progress);
    void videoAvailableChanged(bool available);

    void displayErrorMessage();
  //  void displayPlotWindow();

private:
    void setTrackInfo(const QString &info);
    void setStatusInfo(const QString &info);
    void handleCursor(QMediaPlayer::MediaStatus status);
    void updateDurationInfo(qint64 currentInfo);

//    VideoWidget *videoWidget; making this public....
    QLabel *coverLabel;
    QSlider *slider;
    QLabel *labelDuration;
    QPushButton *nextFrame;
    QPushButton *prevFrame;
   // QPushButton *plotDataButton;
    //QDialog *plotData;

    //NewWindow *newPlotWindow;

    VlcInstance *vlc;
    VlcMediaPlayer *player;

    QString trackInfo;
    QString statusInfo;
    qint64 duration;
};

#endif // PLAYER_H
