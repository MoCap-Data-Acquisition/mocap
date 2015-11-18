#include "playercontrols.h"

#include <QBoxLayout>
#include <QShortcut>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>
#include "player.h"

PlayerControls::PlayerControls(QWidget *parent)
    : QWidget(parent)
    , playerState(Vlc::State::Stopped)
    , playerMuted(false)
    , playButton(0)
    , stopButton(0)
{
    playButton = new QToolButton(this);
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    connect(playButton, SIGNAL(clicked()), this, SLOT(playClicked()));
    playButton->setShortcut(Qt::Key_Space);

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(playButton);

    setLayout(layout);
}

Vlc::State PlayerControls::state() const
{
    return playerState;
}

void PlayerControls::setState()
{
    Vlc::State state = ((Player *) parent())->getPlayerState();
    if (state != playerState) {
        playerState = state;

        switch (state) {
        case Vlc::State::Stopped:
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case Vlc::State::Playing:
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case Vlc::State::Paused:
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case Vlc::State::Ended:
        default:
            break;
        }
    }
}

void PlayerControls::playClicked()
{
    switch (playerState) {
    case Vlc::State::Stopped:
    case Vlc::State::Paused:
        if (((Player *) parent())->currentPosition() < 1.0) emit play();
        break;
    case Vlc::State::Playing:
        emit pause();
        break;
    default:
        break;
    }
}


