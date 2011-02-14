/*
    Copyright (c) 2010-2011 Sune Vuorela <sune@vuorela.dk>

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
#include <QPixmap>
#include <QPainter>

using namespace prison;
/**
 * @cond private
 */
class AbstractBarcode::Private {
  public:
    QString m_data;
    QSizeF m_size;
    QPixmap m_cache;
    QSizeF m_minimum_size;
    AbstractBarcode* q;
    Private(AbstractBarcode* barcode) : m_minimum_size(10,10), q(barcode) { }
};
/**
 * @endcond
 */

AbstractBarcode::AbstractBarcode() : d(new AbstractBarcode::Private(this)) {

}

QString AbstractBarcode::data() const {
  return d->m_data;
}

void AbstractBarcode::paint(QPainter* painter, const QRectF& targetrect) {
  QSizeF size = targetrect.size();
  if(d->m_cache.isNull()||size.toSize()!= d->m_cache.size()) {
    d->m_cache=QPixmap::fromImage(toImage(size));
  }
  QRectF rect(targetrect.left() + targetrect.width() /2 - d->m_cache.size().width() /2,
              targetrect.top() + targetrect.height()/2 - d->m_cache.size().height()/2,
              size.width(),
              size.height());
  painter->drawPixmap(rect.topLeft(),d->m_cache, d->m_cache.rect());
}

void AbstractBarcode::setData(const QString& data) {
  d->m_data=data;
  d->m_cache=QPixmap();
}

QSizeF AbstractBarcode::minimumSize() const {
  return d->m_minimum_size;
}

void AbstractBarcode::setMinimumSize(const QSizeF& minimumSize) {
  d->m_minimum_size = minimumSize;
}

AbstractBarcode::~AbstractBarcode() {
  delete d;
}