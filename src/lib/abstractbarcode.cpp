/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "abstractbarcode.h"
#include "abstractbarcode_p.h"
#include "config-prison.h"
#include "pdf417barcode_p.h"

#include <QColor>
#include <QPainter>
#include <QVariant>

using namespace Prison;

AbstractBarcodePrivate::AbstractBarcodePrivate(AbstractBarcode *barcode)
    : q(barcode)
{
}

bool AbstractBarcodePrivate::sizeTooSmall(const QSizeF &size) const
{
    return m_cache.width() > size.width() || m_cache.height() > size.height();
}

bool AbstractBarcodePrivate::isEmpty() const
{
    switch (m_data.userType()) {
    case QMetaType::QString:
        return m_data.toString().isEmpty();
    case QMetaType::QByteArray:
        return m_data.toByteArray().isEmpty();
    default:
        break;
    }
    return true;
}

void AbstractBarcodePrivate::recompute()
{
    if (m_cache.isNull() && !isEmpty()) {
        m_cache = q->paintImage({});
    }
}

AbstractBarcode::AbstractBarcode(AbstractBarcode::Dimensions dim)
    : d(new AbstractBarcodePrivate(this))
{
    d->m_dimension = dim;
}

QString AbstractBarcode::data() const
{
    return d->m_data.userType() == QMetaType::QString ? d->m_data.toString() : QString();
}

QByteArray AbstractBarcode::byteArrayData() const
{
    return d->m_data.userType() == QMetaType::QByteArray ? d->m_data.toByteArray() : QByteArray();
}

QImage AbstractBarcode::toImage(const QSizeF &size)
{
    d->recompute();
    if (d->m_cache.isNull() || d->sizeTooSmall(size)) {
        return QImage();
    }

    // scale to the requested size, using only full integer factors to keep the code readable
    int scaleX = std::max<int>(1, size.width() / d->m_cache.width());
    int scaleY = std::max<int>(1, size.height() / d->m_cache.height());
    if (dimensions() == TwoDimensions) {
        scaleX = scaleY = std::min(scaleX, scaleY);
    }

    QImage out(d->m_cache.width() * scaleX, d->m_cache.height() * scaleY, d->m_cache.format());
    QPainter p(&out);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);
    p.drawImage(out.rect(), d->m_cache, d->m_cache.rect());
    return out;
}

void AbstractBarcode::setData(const QString &data)
{
    d->m_data = data;
    d->m_cache = QImage();
}

void AbstractBarcode::setData(const QByteArray &data)
{
    d->m_data = data;
    d->m_cache = QImage();
}

QSizeF AbstractBarcode::trueMinimumSize() const
{
    d->recompute();
    return d->m_cache.size();
}

QSizeF AbstractBarcode::preferredSize(qreal devicePixelRatio) const
{
    d->recompute();
    switch (d->m_dimension) {
    case NoDimensions:
        return {};
    case OneDimension:
        return QSizeF(d->m_cache.width() * (devicePixelRatio < 2 ? 2 : 1), std::max(d->m_cache.height(), 50));
    case TwoDimensions:
        // TODO KF6: clean this up once preferredSize is virtual
#if HAVE_ZXING
        // the smallest element of a PDF417 code is 1x 3px, for Aztec/QR/DataMatrix it's just 1x1 px
        if (dynamic_cast<const Pdf417Barcode *>(this)) {
            return d->m_cache.size() * (devicePixelRatio < 2 ? 2 : 1);
        }
#endif
        return d->m_cache.size() * (devicePixelRatio < 2 ? 4 : 2);
    }
    return {};
}

const QColor &AbstractBarcode::backgroundColor() const
{
    return d->m_background;
}

const QColor &AbstractBarcode::foregroundColor() const
{
    return d->m_foreground;
}

void AbstractBarcode::setBackgroundColor(const QColor &backgroundcolor)
{
    if (backgroundcolor != backgroundColor()) {
        d->m_background = backgroundcolor;
        d->m_cache = QImage();
    }
}

void AbstractBarcode::setForegroundColor(const QColor &foregroundcolor)
{
    if (foregroundcolor != foregroundColor()) {
        d->m_foreground = foregroundcolor;
        d->m_cache = QImage();
    }
}

AbstractBarcode::Dimensions AbstractBarcode::dimensions() const
{
    return d->m_dimension;
}

AbstractBarcode::~AbstractBarcode() = default;
