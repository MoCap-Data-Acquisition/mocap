#include "player.h"

#include "playercontrols.h"


#include <QMediaService>
#include <QMediaPlaylist>
#include <QVideoProbe>
#include <QMediaMetaData>
#include <QtWidgets>
#include <QShortcut>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Media.h>

Player::Player(QWidget *parent)
    : QWidget(parent)

{
    vlc = new VlcInstance(VlcCommon::args(), this);
    player = new VlcMediaPlayer(vlc);

    /*
    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    connect(player, SIGNAL(metaDataChanged()), SLOT(metaDataChanged()));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),
            this, SLOT(statusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(bufferStatusChanged(int)), this, SLOT(bufferingProgress(int)));
    connect(player, SIGNAL(videoAvailableChanged(bool)), this, SLOT(videoAvailableChanged(bool)));
    connect(player, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(displayErrorMessage()));
    */

    videoWidget = new VideoWidget(player, this);
    videoWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //slider = new QSlider(Qt::Horizontal, this);
    //slider->setRange(0, (player->length() / 1000));

    labelDuration = new QLabel(this);

    QPushButton *openButton = new QPushButton(tr("Open"), this);

    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    PlayerControls *controls = new PlayerControls(this);
    controls->setState();

    connect(controls, SIGNAL(play()), player, SLOT(play()));
    connect(controls, SIGNAL(pause()), player, SLOT(pause()));
    connect(controls, SIGNAL(stop()), player, SLOT(stop()));
    connect(controls, SIGNAL(stop()), videoWidget, SLOT(update()));
    connect(player, SIGNAL(stateChanged()),
            controls, SLOT(setState()));

    //Frame Buttons
    nextFrame = new QPushButton("", this);
    nextFrame->setEnabled(true);
    connect(nextFrame, SIGNAL(clicked(bool)), this, SLOT(frameUp()));

    prevFrame = new QPushButton("", this);
    prevFrame->setEnabled(true);
    connect(prevFrame, SIGNAL(clicked(bool)), this, SLOT(frameDown()));

    nextFrame->setShortcut(Qt::Key_Right);
    prevFrame->setShortcut(Qt::Key_Left);

    //Graphing Button
//    plotDataButton = new QPushButton(tr("Plot Data"), this);
  //  plotDataButton->setEnabled(true);
   // connect(plotDataButton, SIGNAL(clicked()), this, SLOT(displayPlotWindow()));


    QBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(videoWidget, 2);
    //displayLayout->addWidget(playlistView);

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);
    controlLayout->addWidget(nextFrame);
    controlLayout->addWidget(prevFrame);
    nextFrame->setFlat(true);
    prevFrame->setFlat(true);
    nextFrame->setFixedHeight(1);
    nextFrame->setFixedWidth(1);
    prevFrame->setFixedHeight(1);
    prevFrame->setFixedWidth(1);


    //Graphing Button
  //  controlLayout->addWidget(plotDataButton);


    QBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(displayLayout);
    QHBoxLayout *hLayout = new QHBoxLayout;
    //hLayout->addWidget(slider);
    hLayout->addWidget(labelDuration);
    layout->addLayout(hLayout);
    layout->addLayout(controlLayout);


    setLayout(layout);

    //controls->setEnabled(false);
    openButton->setEnabled(true);


    QStringList arguments = qApp->arguments();
    arguments.removeAt(0);
}

void Player::frameUp()
{
    player->pause();
    player->setPosition(player->position() + (20.0f / player->length()));
}

void Player::frameDown()
{
    player->pause();
    player->setPosition(player->position() - (20.0f / player->length()));
}

Player::~Player()
{

}

qint64 Player::currentTime()
{
    return (qint64) player->length() * player->position();
}

//void Player::openDisplayPlot()
//{
//    newPlotWindow = new NewWindow();

//    newPlotWindow->show();
//}
//void Player::displayPlotWindow()
//{
//   openDisplayPlot();
//}


void Player::open()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Video"));
    VlcMedia *file = new VlcMedia(filename, true, vlc);
    player->open(file);
}

void Player::previousClicked()
{
    // Go to previous track if we are within the first 5 seconds of playback
    // Otherwise, seek to the beginning.
       player->setPosition(0);
}

void Player::jump(const QModelIndex &index)
{
    if (index.isValid()) {
        player->play();
    }
}

void Player::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}

void Player::statusChanged(Vlc::State status)
{
    handleCursor(status);
}

void Player::handleCursor(Vlc::State status)
{
#ifndef QT_NO_CURSOR
    if (status == Vlc::State::Opening ||
        status == Vlc::State::Buffering)
        setCursor(QCursor(Qt::BusyCursor));
    else
        unsetCursor();
#endif
}

Vlc::State Player::getPlayerState()
{
    return player->state();
}

void Player::bufferingProgress(int progress)
{
    setStatusInfo(tr("Buffering %4%").arg(progress));
}

void Player::videoAvailableChanged(bool available)
{
}

void Player::setTrackInfo(const QString &info)
{
    trackInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void Player::setStatusInfo(const QString &info)
{
    statusInfo = info;
    if (!statusInfo.isEmpty())
        setWindowTitle(QString("%1 | %2").arg(trackInfo).arg(statusInfo));
    else
        setWindowTitle(trackInfo);
}

void Player::displayErrorMessage()
{
    //setStatusInfo(player->errorString());
}

void Player::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || duration) {
        QTime currentTime((currentInfo/3600)%60, (currentInfo/60)%60, currentInfo%60, (currentInfo*1000)%1000);
        QTime totalTime((duration/3600)%60, (duration/60)%60, duration%60, (duration*1000)%1000);
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    labelDuration->setText(tStr);
}

