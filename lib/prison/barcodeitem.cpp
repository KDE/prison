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

#include "barcodeitem.h"

#include <QPainter>
#include "abstractbarcode.h"

using namespace prison;

class BarcodeItem::Private {
  public:
    AbstractBarcode* m_barcode;
    Private(AbstractBarcode* barcode) : m_barcode(barcode) {}
};

BarcodeItem::BarcodeItem(QGraphicsItem* parent): QGraphicsItem(parent), d(new BarcodeItem::Private(0)) {

}

BarcodeItem::BarcodeItem(AbstractBarcode* barcode, QGraphicsItem* parent): QGraphicsItem(parent), d(new BarcodeItem::Private(barcode)) {
  
}

void BarcodeItem::setData(const QString& data) {
  if(!d->m_barcode) {
    return;
  }
  prepareGeometryChange();
  d->m_barcode->setData(data);
  update();
}

void BarcodeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
  if(!d->m_barcode) {
    painter->fillRect(boundingRect(),Qt::black);
    return;
  } else {
    d->m_barcode->paint(painter,boundingRect());
  }
}

QRectF BarcodeItem::boundingRect() const {
  if(d->m_barcode) {
    return QRectF(QPointF(0.0,0.0),d->m_barcode->minimumSize());
  } else {
    return QRectF();
  }
}

BarcodeItem::~BarcodeItem() {
  delete d->m_barcode;
  delete d;
}


void BarcodeItem::setBarcode(AbstractBarcode* barcode) {
  delete d->m_barcode;
  d->m_barcode=barcode;
}
