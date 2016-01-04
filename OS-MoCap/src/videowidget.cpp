
#include "videowidget.h"
#include "player.h"

#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>
#include "pointtocsv.h"
#include "mainwindow.h"
#include <QInputDialog>
#include <QColor>

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

void VideoWidget::exportCSVData()
{
     QString filePath = QFileDialog::getSaveFileName(this, "Export CSV Data", "trackingData.csv", ".csv");
     if(filePath.contains(".csv") == false) filePath.append(".csv");
     writePointsToCSV(filePath);
}

void VideoWidget::rotateVideo180() {
    video->rotate180();
}

void VideoWidget::rotateVideoP()
{
    video->rotateP();
}

void VideoWidget::rotateVideoN()
{
    video->rotateN();
}

void VideoWidget::mirrorVideo()
{
    video->mirror();
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
    if(clickAction == 0){}
    if(clickAction == 1){
        //Set Scale
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
        }
    }
    if(clickAction == 2){
        origin = event->pos();
    }
    if(clickAction == 3 && isCalibrated == 2){
        //Point add mode
        auto time = ((Player*)parentWidget())->currentTime();
        if(objectsListVec[0].isEmpty() == true) tZero = time; // set t = 0 at first point
        double myY = (event->y() - origin.y())/calibrationRatio;
        if(origin.x() != 0 && origin.y() != 0) myY *= -1.0;
        qDebug() << "myY = " << QString::number(myY);
        point_t myPoint(currentObjectIndex, (event->x() - origin.x())/calibrationRatio, myY, (time - tZero), currentColor, 0);
        qDebug() << "Point Added: (" << QString::number((int)(event->x() - origin.x())) << ", " << QString::number(myY) << ", " << QString::number(time - tZero) << ")";
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
    QPoint original = {0,0};
    if(origin != original) {
        painter.setBrush(QBrush({255,0,0,150}, Qt::SolidPattern));
        painter.drawEllipse(origin.x() - 7, origin.y()-7, 14, 14);
    }
    double myY = 0;
    for(int i = 0; i < objectsListVec.size(); ++i) {
        for(int j = 0; j < objectsListVec[i].size(); ++j){
            myY = (objectsListVec[i][j].y * calibrationRatio + origin.y());
            if(origin.x() != 0 && origin.y() != 0){
               myY = ((objectsListVec[i][j].y) * calibrationRatio + origin.y()*-1) * -1;
            }
            if(i != currentObjectIndex){
                QColor tColor = objectsListVec[i][j].color;
                tColor.setAlpha(100);
                painter.setBrush(QBrush(tColor, Qt::SolidPattern));
                painter.drawEllipse((objectsListVec[i][j].x * calibrationRatio + origin.x()) - 5, myY - 5, 10, 10);
            }
            if(i == currentObjectIndex){
                painter.setBrush(QBrush(objectsListVec[i][j].color, Qt::SolidPattern));
                painter.drawEllipse((objectsListVec[i][j].x * calibrationRatio + origin.x()) - 5, myY - 5, 10, 10);
            }
        }
    }
  //  qDebug() << "Checking if we need to paint a highlighted point, Last Selected: " << QString::number(lastSelected);
    if(lastSelected >= 0){
        painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        painter.drawEllipse((objectsListVec[currentObjectIndex][lastSelected].x * calibrationRatio + origin.x()) - 5, ((objectsListVec[currentObjectIndex][lastSelected].y * calibrationRatio + (origin.y() * -1)) * -1) - 5, 10, 10);
    }
}
