/*
    SPDX-FileCopyrightText: 2024 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "config-prison-scanner.h"

#include "format_p.h"
#include "imagescanner.h"
#include "imagescanner_p.h"
#include "scanresult.h"
#include "scanresult_p.h"

#include <QImage>

#define ZX_USE_UTF8 1
#include <ZXing/BarcodeFormat.h>
#include <ZXing/ReadBarcode.h>

using namespace Prison;

#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
ZXing::Result ImageScanner::readBarcode(const QImage &image, Format::BarcodeFormats formats)
#else
ZXing::Barcode ImageScanner::readBarcode(const QImage &image, Format::BarcodeFormats formats)
#endif
{
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
    ZXing::DecodeHints hints;
#else
    ZXing::ReaderOptions hints;
#endif
    if (formats != Format::NoFormat) {
        hints.setFormats(Format::toZXing(formats));
#if KZXING_VERSION < QT_VERSION_CHECK(3, 0, 0)
    } else {
        hints.setFormats(ZXing::BarcodeFormats::all());
#endif
    }

    // handle formats ZXing supports directly
    switch (image.format()) {
    case QImage::Format_Invalid:
#if KZXING_VERSION < QT_VERSION_CHECK(1, 4, 0)
        return ZXing::Result(ZXing::DecodeStatus::FormatError);
#else
        return {};
#endif
    case QImage::Format_Mono:
    case QImage::Format_MonoLSB:
    case QImage::Format_Indexed8:
        break; // needs conversion
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied:
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::XRGB, (int)image.bytesPerLine()}, hints);
#else
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::ARGB, (int)image.bytesPerLine()}, hints);
#endif
    case QImage::Format_RGB16:
    case QImage::Format_ARGB8565_Premultiplied:
    case QImage::Format_RGB666:
    case QImage::Format_ARGB6666_Premultiplied:
    case QImage::Format_RGB555:
    case QImage::Format_ARGB8555_Premultiplied:
        break; // needs conversion
    case QImage::Format_RGB888:
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::RGB, (int)image.bytesPerLine()}, hints);
    case QImage::Format_RGB444:
    case QImage::Format_ARGB4444_Premultiplied:
        break; // needs conversion
    case QImage::Format_RGBX8888:
    case QImage::Format_RGBA8888:
    case QImage::Format_RGBA8888_Premultiplied:
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::RGBX, (int)image.bytesPerLine()}, hints);
#else
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::RGBA, (int)image.bytesPerLine()}, hints);
#endif
    case QImage::Format_BGR30:
    case QImage::Format_A2BGR30_Premultiplied:
    case QImage::Format_RGB30:
    case QImage::Format_A2RGB30_Premultiplied:
        break; // needs conversion
    case QImage::Format_Alpha8:
#if KZXING_VERSION < QT_VERSION_CHECK(1, 4, 0)
        return ZXing::Result(ZXing::DecodeStatus::FormatError);
#else
        return {};
#endif
    case QImage::Format_Grayscale8:
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::Lum, (int)image.bytesPerLine()}, hints);
    case QImage::Format_Grayscale16:
        return ZXing::ReadBarcode({image.bits() + 1, image.width(), image.height(), ZXing::ImageFormat::Lum, (int)image.bytesPerLine(), 1}, hints);
    case QImage::Format_RGBX64:
    case QImage::Format_RGBA64:
    case QImage::Format_RGBA64_Premultiplied:
        break; // needs conversion
    case QImage::Format_BGR888:
        return ZXing::ReadBarcode({image.bits(), image.width(), image.height(), ZXing::ImageFormat::BGR, (int)image.bytesPerLine()}, hints);
    case QImage::Format_RGBX16FPx4:
    case QImage::Format_RGBA16FPx4:
    case QImage::Format_RGBA16FPx4_Premultiplied:
    case QImage::Format_RGBX32FPx4:
    case QImage::Format_RGBA32FPx4:
    case QImage::Format_RGBA32FPx4_Premultiplied:
    case QImage::Format_CMYK8888:
        break; // needs conversion

    case QImage::NImageFormats: // silence warnings
#if KZXING_VERSION < QT_VERSION_CHECK(1, 4, 0)
        return ZXing::Result(ZXing::DecodeStatus::FormatError);
#else
        return {};
#endif
    }

    const auto converted = image.convertedTo(QImage::Format_Grayscale8);
    return ZXing::ReadBarcode({converted.bits(), converted.width(), converted.height(), ZXing::ImageFormat::Lum, (int)converted.bytesPerLine()}, hints);
}

ScanResult ImageScanner::scan(const QImage &image, Format::BarcodeFormats formats)
{
    return ScanResultPrivate::fromZXingResult(ImageScanner::readBarcode(image, formats));
}
