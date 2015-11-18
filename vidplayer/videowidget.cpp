
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
    : QGraphicsView(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setBackgroundBrush(QBrush(Qt::black));

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene(this);
    video = new GraphicsVlcItem();
    video->resize(viewport()->size());
    scene->addItem(video);
    setScene(scene);
}

void VideoWidget::setMediaPlayer(VlcMediaPlayer *player) {
    video->setMediaPlayer(player);
    //player->setVideoWidget(video);
}

void VideoWidget::setRotateVideo(bool rotate)
{
    Q_UNUSED(rotate);
    QRectF isize = video->boundingRect();
    video->setTransformOriginPoint(isize.width() / 2, isize.height() / 2);
    video->setRotation(rotate ? 180 : 0);
    videoRotated = rotate;
    scene->update();
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
    QGraphicsView::resizeEvent(event);
    video->resize(viewport()->size());
}

void VideoWidget::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);
    /*setFullScreen(!isfullscreen());
    event->accept();*/
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (isCalibrated == 0) {
        p1 = event->pos();
        isCalibrated = 1;
        QGraphicsView::mousePressEvent(event);
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
        QGraphicsView::mousePressEvent(event);
        viewport()->repaint();
        ((MainWindow *) parent()->parent())->update();
    }
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);
    QPainter painter(this->viewport());
    for(int i = 0; i < objectsListVec.size(); ++i) {
        for(int j = 0; j < objectsListVec[i].size(); ++j){
            painter.setBrush(QBrush(/*objectsListVec[i][j].color*/Qt::blue, Qt::SolidPattern));
            painter.drawEllipse((objectsListVec[i][j].x * calibrationRatio) - 5, (objectsListVec[i][j].y * calibrationRatio) - 5, 10, 10);
        }
    }
}
