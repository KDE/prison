/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "videoscanner.h"
#include "videoscannerframe_p.h"
#include "videoscannerworker_p.h"

#include <QDebug>

using namespace Prison;

namespace Prison
{
class VideoScannerPrivate
{
public:
    void newFrame(const QVideoFrame &videoFrame, bool verticallyFlipped);
    void setResult(VideoScanner *q, const ScanResult &result);

    VideoScannerThread m_thread;
    VideoScannerWorker m_worker;
    QByteArray m_frameDataBuffer; // reused memory when we have to copy frame data
    ScanResult m_result;
    QVariant m_previousContent;
    Format::BarcodeFormats m_formats = Format::NoFormat;
    bool m_workerBusy = false;
};

class VideoScannerFilterRunnable : public QVideoFilterRunnable
{
public:
    VideoScannerFilterRunnable(VideoScannerPrivate *dd);
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags flags) override;

private:
    VideoScannerPrivate *d = nullptr;
};
}

void VideoScannerPrivate::newFrame(const QVideoFrame &videoFrame, bool verticallyFlipped)
{
    // NOTE: this runs in the render thread
    if (!m_workerBusy && videoFrame.isValid()) {
        m_workerBusy = true;

        VideoScannerFrame frame(videoFrame, verticallyFlipped, m_formats);
        // check if we are only allowed to access this in the render thread
        if (frame.copyRequired()) {
            frame.map();
            if (frame.needsConversion()) {
                frame.convertToImage();
            } else {
                frame.copyFrameData(m_frameDataBuffer);
            }
            frame.unmap();
        }

        Q_EMIT m_worker.scanFrameRequest(frame);
    }
}

void VideoScannerPrivate::setResult(VideoScanner *q, const ScanResult &result)
{
    m_workerBusy = false;
    if (m_result == result) {
        return;
    }

    m_result = result;
    Q_EMIT q->resultChanged(result);

    if (m_previousContent == result.content()) {
        return;
    }
    m_previousContent = result.content();
    Q_EMIT q->resultContentChanged(result);
}

VideoScannerFilterRunnable::VideoScannerFilterRunnable(VideoScannerPrivate *dd)
    : d(dd)
{
}

QVideoFrame VideoScannerFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, QVideoFilterRunnable::RunFlags /* flags */)
{
    d->newFrame(*input, surfaceFormat.scanLineDirection() == QVideoSurfaceFormat::BottomToTop);
    return *input;
}

VideoScanner::VideoScanner(QObject *parent)
    : QAbstractVideoFilter(parent)
    , d(new VideoScannerPrivate)
{
    d->m_worker.moveToThread(&d->m_thread);
    connect(
        &d->m_worker,
        &VideoScannerWorker::result,
        this,
        [this](const ScanResult &result) {
            d->setResult(this, result);
        },
        Qt::QueuedConnection);

    d->m_thread.setObjectName(QStringLiteral("Prison Barcode Scanner Worker"));
    d->m_thread.start();
}

VideoScanner::~VideoScanner()
{
    d->m_thread.quit();
    d->m_thread.wait();
}

QVideoFilterRunnable *VideoScanner::createFilterRunnable()
{
    return new VideoScannerFilterRunnable(d.get());
}

ScanResult VideoScanner::result() const
{
    return d->m_result;
}

Format::BarcodeFormats VideoScanner::formats() const
{
    return d->m_formats;
}

void VideoScanner::setFormats(Format::BarcodeFormats formats)
{
    if (d->m_formats == formats) {
        return;
    }

    d->m_formats = formats;
    Q_EMIT formatsChanged();
}

#include "moc_videoscanner.cpp"
