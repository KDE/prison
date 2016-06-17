/*
    Copyright (c) 2010-2016 Sune Vuorela <sune@vuorela.dk>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#include "abstractbarcode.h"
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
    QSizeF m_size;
    QImage m_cache;
    QColor m_foreground;
    QColor m_background;
    QSizeF m_minimum_size;
    AbstractBarcode* q;
    bool sizeTooSmall(const QSizeF& size) {
        if(m_minimum_size.width() > size.width()) {
            return true;
        } else if(m_minimum_size.height() > size.height()) {
            return true;
        }
        return false;
    }
    Private(AbstractBarcode* barcode) : m_foreground(Qt::black), m_background(Qt::white), m_minimum_size(10,10), q(barcode) { }
};
/**
 * @endcond
 */

AbstractBarcode::AbstractBarcode() : d(new AbstractBarcode::Private(this)) {

}

QString AbstractBarcode::data() const {
  return d->m_data;
}


QImage AbstractBarcode::toImage(const QSizeF& size) {
    if(d->sizeTooSmall(size)) {
        d->m_cache = QImage();
        return QImage();
    }
    if(d->m_cache.isNull() || size != d->m_size) {
        d->m_size = size;
        d->m_cache = paintImage(size);
        return d->m_cache;
    }
    return d->m_cache;
}

void AbstractBarcode::setData(const QString& data) {
  d->m_data=data;
  d->m_cache=QImage();
  d->m_size=QSize();
  d->m_minimum_size=QSizeF(10,10);
}

QSizeF AbstractBarcode::minimumSize() const {
  return d->m_minimum_size;
}

void AbstractBarcode::setMinimumSize(const QSizeF& minimumSize) {
    d->m_minimum_size = minimumSize;
    if(minimumSize.width() > d->m_size.width() || minimumSize.height() > d->m_size.height()) {
        d->m_cache = QImage();
    }
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

AbstractBarcode::~AbstractBarcode() {
    delete d;
}
