
#include "videowidget.h"
#include "player.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include "pointtocsv.h"
#include "mainwindow.h"
#include <QInputDialog>

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_OpaquePaintEvent);

    video = new VlcWidgetVideo(this);
    video->resize(size());
}

void VideoWidget::setMediaPlayer(VlcMediaPlayer *player) {
    video->setMediaPlayer(player);
    player->setVideoWidget(video);
}

void VideoWidget::setRotateVideo(bool rotate)
{
    /*
    QSizeF isize = item->size();
    item->setTransformOriginPoint(isize.width() / 2, isize.height() / 2);
    item->setRotation(rotate ? 180 : 0);
    videoRotated = rotate;
    scene->update();
    */
}
void VideoWidget::exportCSVData()
{
     QString filePath = QFileDialog::getSaveFileName(this, "Export CSV Data", "trackingData.csv", ".csv");
     if(filePath.contains(".csv") == false) filePath.append(".csv");
     writePointsToCSV(filePath);
}

void VideoWidget::toggleRotateVideo()
{
    setRotateVideo(!videoRotated);
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    video->resize(size());
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    QWidget::keyPressEvent(event);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    /*setFullScreen(!isfullscreen());
    event->accept();*/
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (isCalibrated == 0) {
        p1 = event->pos();
        isCalibrated = 1;
        QWidget::mousePressEvent(event);
    } else if (isCalibrated == 1) {
        QPoint p2 = event->pos();
        QPoint dist = p2 - p1;
        double pixels = std::sqrt(QPoint::dotProduct(dist,dist));
        double metres = QInputDialog::getDouble(this, "Input the calibration distance in metres", "distance", 1.0);
        calibrationRatio = pixels/metres;
        isCalibrated = 2;
    } else {
        auto time = ((Player*)parentWidget())->currentTime();
        point_t myPoint(currentObjectIndex, (event->x())/calibrationRatio, (event->y())/calibrationRatio, time, currentColor);
        qDebug() << "Point Added: (" << QString::number((int)event->x()) << ", " << QString::number((int) event->y()) << ", " << QString::number(time) << ")";
        objectsListVec[currentObjectIndex].push_back(myPoint);
        objectsListDirty = true;
        drawPoint = myPoint;
        QWidget::mousePressEvent(event);
        ((MainWindow *) parent()->parent())->update();
    }
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    /*
    QPainter painter(this);
    for(int i = 0; i < objectsListVec.size(); ++i) {
        for(int j = 0; j < objectsListVec[i].size(); ++j){
            painter.setBrush(QBrush(objectsListVec[i][j].color, Qt::SolidPattern));
            painter.drawEllipse((objectsListVec[i][j].x * calibrationRatio) - 5, (objectsListVec[i][j].y * calibrationRatio) - 5, 10, 10);
        }
    }
    */
}
