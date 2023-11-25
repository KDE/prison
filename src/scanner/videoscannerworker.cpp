/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "config-prison-scanner.h"
#include "format_p.h"
#include "scanresult_p.h"
#include "videoscannerframe_p.h"
#include "videoscannerworker_p.h"

#include <QDebug>
#include <QImage>
#include <QTransform>

#define ZX_USE_UTF8 1
#include <ZXing/ReadBarcode.h>
#include <ZXing/TextUtfEncoding.h>

using namespace Prison;

VideoScannerWorker::VideoScannerWorker(QObject *parent)
    : QObject(parent)
{
    connect(this, &VideoScannerWorker::scanFrameRequest, this, &VideoScannerWorker::slotScanFrame, Qt::QueuedConnection);
}

void VideoScannerWorker::slotScanFrame(VideoScannerFrame frame)
{
#if ZXING_VERSION < QT_VERSION_CHECK(1, 4, 0)
    ZXing::Result zxRes(ZXing::DecodeStatus::FormatError);
#else
    ZXing::Result zxRes;
#endif
    ZXing::DecodeHints hints;
    hints.setFormats(frame.formats() == Format::NoFormat ? ZXing::BarcodeFormats::all() : Format::toZXing(frame.formats()));

    frame.map();
    switch (frame.pixelFormat()) {
    case QVideoFrameFormat::Format_Invalid: // already checked before we get here
        break;
    // formats ZXing can consume directly
    case QVideoFrameFormat::Format_ARGB8888:
    case QVideoFrameFormat::Format_ARGB8888_Premultiplied:
    case QVideoFrameFormat::Format_XRGB8888:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::XRGB, frame.bytesPerLine()}, hints);
        break;
    case QVideoFrameFormat::Format_BGRA8888:
    case QVideoFrameFormat::Format_BGRA8888_Premultiplied:
    case QVideoFrameFormat::Format_BGRX8888:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::BGRX, frame.bytesPerLine()}, hints);
        break;
    case QVideoFrameFormat::Format_ABGR8888:
    case QVideoFrameFormat::Format_XBGR8888:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::XBGR, frame.bytesPerLine()}, hints);
        break;
    case QVideoFrameFormat::Format_RGBA8888:
    case QVideoFrameFormat::Format_RGBX8888:
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::RGBX, frame.bytesPerLine()}, hints);
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
        zxRes = ZXing::ReadBarcode({frame.bits(), frame.width(), frame.height(), ZXing::ImageFormat::Lum, frame.bytesPerLine()}, hints);
        break;
    }
    frame.unmap();

    // process scan result
    ScanResult scanResult;
    if (zxRes.isValid()) {
        auto res = ScanResultPrivate::get(scanResult);

#if ZXING_VERSION < QT_VERSION_CHECK(1, 4, 0)
        // distinguish between binary and text content
        const auto hasWideChars = std::any_of(zxRes.text().begin(), zxRes.text().end(), [](auto c) {
            return c > 255;
        });
        const auto hasControlChars = std::any_of(zxRes.text().begin(), zxRes.text().end(), [](auto c) {
            return c < 0x20 && c != 0x0a && c != 0x0d;
        });
        if (hasWideChars || !hasControlChars) {
            res->content = QString::fromStdString(ZXing::TextUtfEncoding::ToUtf8(zxRes.text()));
        } else {
            QByteArray b;
            b.resize(zxRes.text().size());
            std::copy(zxRes.text().begin(), zxRes.text().end(), b.begin());
            res->content = b;
        }
#else
        if (zxRes.contentType() == ZXing::ContentType::Text) {
            res->content = QString::fromStdString(zxRes.text());
        } else {
            QByteArray b;
            b.resize(zxRes.bytes().size());
            std::copy(zxRes.bytes().begin(), zxRes.bytes().end(), b.begin());
            res->content = b;
        }
#endif

        // determine the bounding rect
        // the cooridinates we get from ZXing are a polygon, we need to determine the
        // bounding rect manually from its coordinates
        const auto p = zxRes.position();
        int x1 = std::numeric_limits<int>::max();
        int y1 = std::numeric_limits<int>::max();
        int x2 = std::numeric_limits<int>::min();
        int y2 = std::numeric_limits<int>::min();
        for (int i = 0; i < 4; ++i) {
            x1 = std::min(x1, p[i].x);
            y1 = std::min(y1, p[i].y);
            x2 = std::max(x2, p[i].x);
            y2 = std::max(y2, p[i].y);
        }
        res->boundingRect = QRect(QPoint(x1, y1), QPoint(x2, y2));

        // apply frame transformations to the bounding rect
        if (frame.isVerticallyFlipped()) {
            QTransform t;
            t.scale(1, -1);
            t.translate(0, -frame.height());
            res->boundingRect = t.mapRect(res->boundingRect);
        }

        res->format = Format::toFormat(zxRes.format());
    }

    Q_EMIT result(scanResult);
}

void VideoScannerThread::run()
{
    exec();
}

#include "moc_videoscannerworker_p.cpp"
