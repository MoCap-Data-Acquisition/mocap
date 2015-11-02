#include "histogramwidget.h"
#include <QPainter>

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget(parent)
    , m_levels(128)
    , m_isBusy(false)
{
    m_processor.moveToThread(&m_processorThread);
    qRegisterMetaType<QVector<qreal> >("QVector<qreal>");
    connect(&m_processor, SIGNAL(histogramReady(QVector<qreal>)), SLOT(setHistogram(QVector<qreal>)));
    m_processorThread.start(QThread::LowestPriority);
}

HistogramWidget::~HistogramWidget()
{
    m_processorThread.quit();
    m_processorThread.wait(10000);
}

void HistogramWidget::processFrame(QVideoFrame frame)
{
    if (m_isBusy)
        return; //drop frame

    m_isBusy = true;
    QMetaObject::invokeMethod(&m_processor, "processFrame",
                              Qt::QueuedConnection, Q_ARG(QVideoFrame, frame), Q_ARG(int, m_levels));
}

void HistogramWidget::setHistogram(QVector<qreal> histogram)
{
    m_isBusy = false;
    m_histogram = histogram;
    update();
}

void HistogramWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    if (m_histogram.isEmpty()) {
        painter.fillRect(0, 0, width(), height(), QColor::fromRgb(0, 0, 0));
        return;
    }

    qreal barWidth = width() / (qreal)m_histogram.size();

    for (int i = 0; i < m_histogram.size(); i++) {
        qreal h = m_histogram[i] * height();
        // draw level
        painter.fillRect(barWidth * i, height() - h, barWidth * (i + 1), height(), Qt::red);
        // clear the rest of the control
        painter.fillRect(barWidth * i, 0, barWidth * (i + 1), height() - h, Qt::black);
    }
}

void FrameProcessor::processFrame(QVideoFrame frame, int levels)
{
    QVector<qreal> histogram(levels);

    do {
        if (!levels)
            break;

        if (!frame.map(QAbstractVideoBuffer::ReadOnly))
            break;

        if (frame.pixelFormat() == QVideoFrame::Format_YUV420P ||
            frame.pixelFormat() == QVideoFrame::Format_NV12) {
            // Process YUV data
            uchar *b = frame.bits();
            for (int y = 0; y < frame.height(); y++) {
                uchar *lastPixel = b + frame.width();
                for (uchar *curPixel = b; curPixel < lastPixel; curPixel++)
                    histogram[(*curPixel * levels) >> 8] += 1.0;
                b += frame.bytesPerLine();
            }
        } else {
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
            if (imageFormat != QImage::Format_Invalid) {
                // Process RGB data
                QImage image(frame.bits(), frame.width(), frame.height(), imageFormat);
                image = image.convertToFormat(QImage::Format_RGB32);

                const QRgb* b = (const QRgb*)image.bits();
                for (int y = 0; y < image.height(); y++) {
                    const QRgb *lastPixel = b + frame.width();
                    for (const QRgb *curPixel = b; curPixel < lastPixel; curPixel++)
                        histogram[(qGray(*curPixel) * levels) >> 8] += 1.0;
                    b = (const QRgb*)((uchar*)b + image.bytesPerLine());
                }
            }
        }

        // find maximum value
        qreal maxValue = 0.0;
        for (int i = 0; i < histogram.size(); i++) {
            if (histogram[i] > maxValue)
                maxValue = histogram[i];
        }

        if (maxValue > 0.0) {
            for (int i = 0; i < histogram.size(); i++)
                histogram[i] /= maxValue;
        }

        frame.unmap();
    } while (false);

    emit histogramReady(histogram);
}
