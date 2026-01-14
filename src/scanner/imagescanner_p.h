/*
    SPDX-FileCopyrightText: 2024 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_IMAGESCANNER_P_H
#define PRISON_IMAGESCANNER_P_H

#include "config-prison-scanner.h"

#include "format.h"

#define ZX_USE_UTF8 1
#if ZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
#include <ZXing/Result.h>
#else
#include <ZXing/Barcode.h>
#endif

class QImage;

namespace Prison
{

namespace ImageScanner
{

#if ZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
[[nodiscard]] ZXing::Result readBarcode(const QImage &image, Format::BarcodeFormats formats);
#else
[[nodiscard]] ZXing::Barcode readBarcode(const QImage &image, Format::BarcodeFormats formats);
#endif
}
}

#endif // PRISON_IMAGESCANNER_P_H
