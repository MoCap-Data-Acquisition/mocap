#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QWidget>

#include <VLCQtCore/Enums.h>

class QAbstractButton;
class QAbstractSlider;
class QComboBox;

class PlayerControls : public QWidget
{
    Q_OBJECT

public:
    PlayerControls(QWidget *parent = 0);
    Vlc::State state() const;

public slots:
    void setState();
    void playClicked();
signals:
    void play();
    void pause();
    void stop();

private:
    Vlc::State playerState;
    bool playerMuted;
    QAbstractButton *playButton;
    QAbstractButton *stopButton;
};

#endif // PLAYERCONTROLS_H
