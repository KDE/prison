/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_SCANRESULT_P_H
#define PRISON_SCANRESULT_P_H

#include "config-prison-scanner.h"

#include "scanresult.h"

#include <QSharedData>
#include <QTransform>

#define ZX_USE_UTF8 1
#if ZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
#include <ZXing/Result.h>
#else
#include <ZXing/Barcode.h>
#endif

namespace Prison
{

class ScanResultPrivate : public QSharedData
{
public:
    [[nodiscard]] static ScanResult fromZXingResult(const ZXing::Result &zxRes, const QTransform &transform = QTransform());

    QVariant content;
    QRect boundingRect;
    Format::BarcodeFormat format = Format::NoFormat;
};

}
#endif // PRISON_SCANRESULT_P_H
