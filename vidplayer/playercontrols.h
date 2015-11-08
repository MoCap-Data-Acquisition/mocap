#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QMediaPlayer>
#include <QWidget>

class QAbstractButton;
class QAbstractSlider;
class QComboBox;

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    PlayerControls(QWidget *parent = 0);

    QMediaPlayer::State state() const;

public slots:
    void setState(QMediaPlayer::State state);

signals:
    void play();
    void pause();
    void stop();

private slots:
    void playClicked();

private:
    QMediaPlayer::State playerState;
    bool playerMuted;
    QAbstractButton *playButton;
    QAbstractButton *stopButton;
};

#endif // PLAYERCONTROLS_H
