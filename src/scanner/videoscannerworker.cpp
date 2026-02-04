/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "config-prison-scanner.h"
#include "format_p.h"
#include "imagescanner_p.h"
#include "scanresult.h"
#include "scanresult_p.h"
#include "videoscannerframe_p.h"
#include "videoscannerworker_p.h"

#include <QDebug>
#include <QImage>
#include <QTransform>

#define ZX_USE_UTF8 1
#include <ZXing/ReadBarcode.h>

using namespace Prison;

VideoScannerWorker::VideoScannerWorker(QObject *parent)
    : QObject(parent)
{
    connect(this, &VideoScannerWorker::scanFrameRequest, this, &VideoScannerWorker::slotScanFrame, Qt::QueuedConnection);
}

void VideoScannerWorker::slotScanFrame(VideoScannerFrame frame)
{
#if KZXING_VERSION < QT_VERSION_CHECK(1, 4, 0)
    ZXing::Result zxRes(ZXing::DecodeStatus::FormatError);
#elif KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
    ZXing::Result zxRes;
#else
    ZXing::Barcode zxRes;
#endif
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
    ZXing::DecodeHints hints;
#else
    ZXing::ReaderOptions hints;
#endif
    if (frame.formats() != Format::NoFormat) {
        hints.setFormats(Format::toZXing(frame.formats()));
#if KZXING_VERSION < QT_VERSION_CHECK(3, 0, 0)
    } else {
        hints.setFormats(ZXing::BarcodeFormats::all());
#endif
    }

    frame.map();
    switch (frame.pixelFormat()) {
    case QVideoFrameFormat::Format_Invalid: // already checked before we get here
        break;
    // formats ZXing can consume directly
    case QVideoFrameFormat::Format_ARGB8888:
    case QVideoFrameFormat::Format_ARGB8888_Premultiplied:
    case QVideoFrameFormat::Format_XRGB8888:
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::XRGB, frame.bytesPerLine()}, hints);
#else
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::ARGB, frame.bytesPerLine()}, hints);
#endif
        break;
    case QVideoFrameFormat::Format_BGRA8888:
    case QVideoFrameFormat::Format_BGRA8888_Premultiplied:
    case QVideoFrameFormat::Format_BGRX8888:
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::BGRX, frame.bytesPerLine()}, hints);
#else
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::BGRA, frame.bytesPerLine()}, hints);
#endif
        break;
    case QVideoFrameFormat::Format_ABGR8888:
    case QVideoFrameFormat::Format_XBGR8888:
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::XBGR, frame.bytesPerLine()}, hints);
#else
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::ABGR, frame.bytesPerLine()}, hints);
#endif
        break;
    case QVideoFrameFormat::Format_RGBA8888:
    case QVideoFrameFormat::Format_RGBX8888:
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::RGBX, frame.bytesPerLine()}, hints);
#else
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::RGBA, frame.bytesPerLine()}, hints);
#endif
        break;
    case QVideoFrameFormat::Format_AYUV:
    case QVideoFrameFormat::Format_AYUV_Premultiplied:
        zxRes = ZXing::ReadBarcode({frame.bits() + 1, frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine(), 4}, hints);
        break;
    case QVideoFrameFormat::Format_YUV420P:
    case QVideoFrameFormat::Format_YUV422P:
    case QVideoFrameFormat::Format_YV12:
    case QVideoFrameFormat::Format_NV12:
    case QVideoFrameFormat::Format_NV21:
    case QVideoFrameFormat::Format_IMC1:
    case QVideoFrameFormat::Format_IMC2:
    case QVideoFrameFormat::Format_IMC3:
    case QVideoFrameFormat::Format_IMC4:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine()}, hints);
        break;
    case QVideoFrameFormat::Format_UYVY:
        zxRes = ZXing::ReadBarcode({frame.bits() + 1, frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine(), 2}, hints);
        break;
    case QVideoFrameFormat::Format_YUYV:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine(), 2}, hints);
        break;
    case QVideoFrameFormat::Format_Y8:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine()}, hints);
        break;
    case QVideoFrameFormat::Format_Y16:
        zxRes = ZXing::ReadBarcode({frame.bits() + 1, frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine(), 1}, hints);
        break;
    case QVideoFrameFormat::Format_P010:
    case QVideoFrameFormat::Format_P016:
    case QVideoFrameFormat::Format_YUV420P10:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine(), 1}, hints);
        break;

    // formats needing conversion before ZXing can consume them
    case QVideoFrameFormat::Format_Jpeg:
    case QVideoFrameFormat::Format_SamplerExternalOES:
    case QVideoFrameFormat::Format_SamplerRect:
        frame.convertToImage();
        zxRes = ImageScanner::readBarcode(frame.image(), frame.formats());
        break;
    }
    frame.unmap();

    // process scan result
    if (zxRes.isValid()) {
        QTransform t;
        if (frame.isVerticallyFlipped()) {
            t.scale(1, -1);
            t.translate(0, -frame.height());
        }
        Q_EMIT result(ScanResultPrivate::fromZXingResult(zxRes, t));
    } else {
        Q_EMIT result(ScanResult());
    }
}

void VideoScannerThread::run()
{
    exec();
}

#include "moc_videoscannerworker_p.cpp"
