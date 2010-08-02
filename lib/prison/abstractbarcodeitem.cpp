/*
    Copyright (c) 2010 Sune Vuorela <sune@vuorela.dk>

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

#include "abstractbarcodeitem.h"
#include <qpainter.h>

using namespace prison;

class AbstractBarcodeItem::Private {
  public:
    QString data;
    QPixmap cache;
    bool dirty;
    QSizeF size;
    Private() : dirty(true), size(10.0,10.0) { }
    
};

AbstractBarcodeItem::AbstractBarcodeItem(QGraphicsItem* parent, QGraphicsScene* scene) : QGraphicsItem(parent, scene),
    d(new AbstractBarcodeItem::Private()) {

}


void AbstractBarcodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
  if(d->dirty) {
    d->cache = updateImage();
    d->dirty = false;
  }

  painter->drawPixmap(boundingRect(),d->cache,d->cache.rect());
}

QRectF AbstractBarcodeItem::boundingRect() const {
  return QRectF(QPointF(0,0),d->size);
}

const QString& AbstractBarcodeItem::data() const {
  return d->data;
}

void AbstractBarcodeItem::setData(const QString& data) {
  d->data = data;
  QPixmap newimage = updateImage();
  QSizeF newsize = QSizeF(newimage.size());
  if(newsize!=d->size) {
    prepareGeometryChange();
    d->size=newsize;
  }
  d->cache=newimage;
  d->dirty=false;
}


const QSizeF& prison::AbstractBarcodeItem::imageSize() const {
  return d->size;
}

AbstractBarcodeItem::~AbstractBarcodeItem() {
  delete d;
}

