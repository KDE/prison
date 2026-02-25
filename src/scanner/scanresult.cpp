/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "config-prison-scanner.h"

#include "format_p.h"
#include "scanresult.h"
#include "scanresult_p.h"

#define ZX_USE_UTF8 1
#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
#include <ZXing/TextUtfEncoding.h>
#endif

using namespace Prison;

ScanResult::ScanResult()
    : d(new ScanResultPrivate)
{
}

ScanResult::ScanResult(const ScanResult &) = default;
ScanResult::~ScanResult() = default;
ScanResult &ScanResult::operator=(const ScanResult &) = default;

bool ScanResult::operator==(const ScanResult &other) const
{
    return d->content == other.d->content && d->boundingRect == other.d->boundingRect && d->format == other.d->format;
}

bool ScanResult::hasContent() const
{
    return !d->content.isNull();
}

QVariant ScanResult::content() const
{
    return d->content;
}

bool ScanResult::hasText() const
{
    return d->content.userType() == QMetaType::QString;
}

QString ScanResult::text() const
{
    return hasText() ? d->content.toString() : QString();
}

bool ScanResult::hasBinaryData() const
{
    return d->content.userType() == QMetaType::QByteArray;
}

QByteArray ScanResult::binaryData() const
{
    return hasBinaryData() ? d->content.toByteArray() : QByteArray();
}

Format::BarcodeFormat ScanResult::format() const
{
    return d->format;
}

QRect ScanResult::boundingRect() const
{
    return d->boundingRect;
}

#if KZXING_VERSION < QT_VERSION_CHECK(2, 3, 0)
ScanResult ScanResultPrivate::fromZXingResult(const ZXing::Result &zxRes, const QTransform &transform)
#else
ScanResult ScanResultPrivate::fromZXingResult(const ZXing::Barcode &zxRes, const QTransform &transform)
#endif
{
    ScanResult res;
    if (!zxRes.isValid()) {
        return res;
    }

    bool isText = zxRes.contentType() == ZXing::ContentType::Text;
    if (zxRes.contentType() == ZXing::ContentType::GS1) {
        isText = std::ranges::none_of(zxRes.text(), [](auto c) {
            return c < 0x20 && c != 0x0a && c != 0x0d;
        });
    }

    if (isText) {
        res.d->content = QString::fromStdString(zxRes.text());
    } else {
        QByteArray b;
        b.resize(zxRes.bytes().size());
        std::copy(zxRes.bytes().begin(), zxRes.bytes().end(), b.begin());
        res.d->content = b;
    }

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
    res.d->boundingRect = QRect(QPoint(x1, y1), QPoint(x2, y2));

    // apply frame transformations to the bounding rect
    res.d->boundingRect = transform.mapRect(res.d->boundingRect);
    res.d->format = Format::toFormat(zxRes.format());
    return res;
}

#include "moc_scanresult.cpp"
