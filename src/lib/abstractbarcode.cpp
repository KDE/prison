/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "abstractbarcode.h"

#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QColor>

using namespace Prison;
/**
 * @cond private
 */
class AbstractBarcode::Private {
  public:
    QString m_data;
    QImage m_cache;
    QColor m_foreground = Qt::black;
    QColor m_background = Qt::white;
    QSizeF m_minimum_size;
    AbstractBarcode::Dimensions m_dimension = AbstractBarcode::NoDimensions;
    AbstractBarcode* q;

    bool sizeTooSmall(const QSizeF& size) const {
        if(m_minimum_size.width() > size.width()) {
            return true;
        } else if(m_minimum_size.height() > size.height()) {
            return true;
        }
        return false;
    }

    void recompute()
    {
        if (m_cache.isNull() && !m_data.isEmpty()) {
            m_cache = q->paintImage({});
        }
    }

    Private(AbstractBarcode* barcode) : q(barcode) { }
};
/**
 * @endcond
 */

#if PRISON_BUILD_DEPRECATED_SINCE(5, 69)
AbstractBarcode::AbstractBarcode() : d(new AbstractBarcode::Private(this)) {

}
#endif

AbstractBarcode::AbstractBarcode(AbstractBarcode::Dimensions dim) :
    d(new AbstractBarcode::Private(this))
{
    d->m_dimension = dim;
}

QString AbstractBarcode::data() const {
  return d->m_data;
}


QImage AbstractBarcode::toImage(const QSizeF& size)
{
    d->recompute();
    if (d->m_cache.isNull() || d->sizeTooSmall(size)) {
        return QImage();
    }

    // scale to the requested size, using only full integer factors to keep the code readable
    int scaleX = std::max<int>(1, size.width() / d->m_minimum_size.width());
    int scaleY = std::max<int>(1, size.height() / d->m_minimum_size.height());
    if (dimensions() == TwoDimensions) {
        scaleX = scaleY = std::min(scaleX, scaleY);
    }

    QImage out(d->m_minimum_size.width() * scaleX, d->m_minimum_size.height() * scaleY, d->m_cache.format());
    QPainter p(&out);
    p.setRenderHint(QPainter::SmoothPixmapTransform, false);
    p.drawImage(out.rect(), d->m_cache, d->m_cache.rect());
    return out;
}

void AbstractBarcode::setData(const QString& data) {
  d->m_data=data;
  d->m_cache=QImage();
  d->m_minimum_size = QSize();
}

QSizeF AbstractBarcode::minimumSize() const
{
    d->recompute();

    // ### backward compatibility: this is applying minimum size behavior that the specific
    // implementations were doing prior to 5.69. This is eventually to be dropped.
    if (!d->m_minimum_size.isValid()) {
        return {};
    }
    switch (d->m_dimension) {
        case NoDimensions:
            return {};
        case OneDimension:
            return QSizeF(d->m_minimum_size.width(), std::max(d->m_minimum_size.height(), 10.0));
        case TwoDimensions:
            return d->m_minimum_size * 4;
    }

    return d->m_minimum_size;
}

void AbstractBarcode::setMinimumSize(const QSizeF& minimumSize)
{
    d->m_minimum_size = minimumSize;
}

const QColor& AbstractBarcode::backgroundColor() const {
    return d->m_background;
}

const QColor& AbstractBarcode::foregroundColor() const {
    return d->m_foreground;
}

void AbstractBarcode::setBackgroundColor(const QColor& backgroundcolor) {
  if(backgroundcolor!=backgroundColor()) {
    d->m_background=backgroundcolor;
    d->m_cache=QImage();
  }
}

void AbstractBarcode::setForegroundColor(const QColor& foregroundcolor) {
    if(foregroundcolor!=foregroundColor()) {
        d->m_foreground=foregroundcolor;
        d->m_cache=QImage();
    }
}

AbstractBarcode::Dimensions AbstractBarcode::dimensions() const
{
    return d->m_dimension;
}

AbstractBarcode::~AbstractBarcode() {
    delete d;
}
