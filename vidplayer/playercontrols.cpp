#include "playercontrols.h"

#include <QBoxLayout>
#include <QShortcut>
#include <QSlider>
#include <QStyle>
#include <QToolButton>
#include <QComboBox>

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

    stopButton = new QToolButton(this);
    stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    stopButton->setEnabled(false);

    connect(stopButton, SIGNAL(clicked()), this, SIGNAL(stop()));

    QBoxLayout *layout = new QHBoxLayout;
    layout->setMargin(0);
    layout->addWidget(stopButton);
    layout->addWidget(playButton);

    setLayout(layout);
}

Vlc::State PlayerControls::state() const
{
    return playerState;
}

void PlayerControls::setState(Vlc::State state)
{
    if (state != playerState) {
        playerState = state;

        switch (state) {
        case Vlc::Stopped:
            stopButton->setEnabled(false);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        case Vlc::Playing:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
            break;
        case Vlc::Paused:
            stopButton->setEnabled(true);
            playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
            break;
        }
    }
}

void PlayerControls::playClicked()
{
    switch (playerState) {
    case Vlc::State::Stopped:
    case Vlc::State::Paused:
        emit play();
        break;
    case Vlc::State::Playing:
        emit pause();
        break;
    }
}


