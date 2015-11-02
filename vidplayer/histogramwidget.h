#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QThread>
#include <QVideoFrame>
#include <QWidget>

class FrameProcessor: public QObject
{
    Q_OBJECT

public slots:
    void processFrame(QVideoFrame frame, int levels);

signals:
    void histogramReady(QVector<qreal> histogram);
};

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = 0);
    ~HistogramWidget();
    void setLevels(int levels) { m_levels = levels; }

public slots:
    void processFrame(QVideoFrame frame);
    void setHistogram(QVector<qreal> histogram);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QVector<qreal> m_histogram;
    int m_levels;
    FrameProcessor m_processor;
    QThread m_processorThread;
    bool m_isBusy;
};

#endif // HISTOGRAMWIDGET_H
