/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "abstractbarcode.h"

#include <QColor>
#include <QPainter>
#include <QVariant>

using namespace Prison;
/**
 * @cond private
 */
class Prison::AbstractBarcodePrivate
{
public:
    QVariant m_data;
    QImage m_cache;
    QColor m_foreground = Qt::black;
    QColor m_background = Qt::white;
    AbstractBarcode::Dimensions m_dimension = AbstractBarcode::NoDimensions;
    AbstractBarcode *q;

    bool sizeTooSmall(const QSizeF &size) const
    {
        return m_cache.width() > size.width() || m_cache.height() > size.height();
    }

    bool isEmpty() const
    {
        switch (m_data.type()) {
        case QVariant::String:
            return m_data.toString().isEmpty();
        case QVariant::ByteArray:
            return m_data.toByteArray().isEmpty();
        default:
            break;
        }
        return true;
    }

    void recompute()
    {
        if (m_cache.isNull() && !isEmpty()) {
            m_cache = q->paintImage({});
        }
    }

    explicit AbstractBarcodePrivate(AbstractBarcode *barcode)
        : q(barcode)
    {
    }
};
/**
 * @endcond
 */

#if PRISON_BUILD_DEPRECATED_SINCE(5, 69)
AbstractBarcode::AbstractBarcode()
    : d(new AbstractBarcodePrivate(this))
{
}
#endif

AbstractBarcode::AbstractBarcode(AbstractBarcode::Dimensions dim)
    : d(new AbstractBarcodePrivate(this))
{
    d->m_dimension = dim;
}

QString AbstractBarcode::data() const
{
    return d->m_data.type() == QVariant::String ? d->m_data.toString() : QString();
}

QByteArray AbstractBarcode::byteArrayData() const
{
    return d->m_data.type() == QVariant::ByteArray ? d->m_data.toByteArray() : QByteArray();
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

#if PRISON_BUILD_DEPRECATED_SINCE(5, 72)
QSizeF AbstractBarcode::minimumSize() const
{
    d->recompute();

    // ### backward compatibility: this is applying minimum size behavior that the specific
    // implementations were doing prior to 5.69. This is eventually to be dropped.
    if (d->m_cache.isNull()) {
        return {};
    }
    switch (d->m_dimension) {
    case NoDimensions:
        return {};
    case OneDimension:
        return QSizeF(d->m_cache.width(), std::max(d->m_cache.height(), 10));
    case TwoDimensions:
        return d->m_cache.size() * 4;
    }

    return d->m_cache.size();
}
#endif

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
        return d->m_cache.size() * (devicePixelRatio < 2 ? 4 : 2);
    }
    return {};
}

#if PRISON_BUILD_DEPRECATED_SINCE(5, 69)
void AbstractBarcode::setMinimumSize(const QSizeF &minimumSize)
{
    Q_UNUSED(minimumSize);
}
#endif

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
