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

#include "barcodewidget.h"
#include "abstractbarcode.h"
#include <QResizeEvent>
#include <QPainter>

using namespace prison;

/**
 * @cond PRIVATE
 */
class BarcodeWidget::Private {
  public:
    AbstractBarcode* m_barcode;
    BarcodeWidget* q;
    Private(AbstractBarcode* barcode,BarcodeWidget* parent) : m_barcode(barcode), q(parent) {
    }
};
/**
 * @endcond
 */

BarcodeWidget::BarcodeWidget(QWidget* parent): QWidget(parent), d(new BarcodeWidget::Private(0,this)) {
}

BarcodeWidget::BarcodeWidget(AbstractBarcode* barcode, QWidget* parent) : QWidget(parent), d(new BarcodeWidget::Private(barcode,this)) {

}



void BarcodeWidget::setData(QString data) {
  if(d->m_barcode)
    d->m_barcode->setData(data);
  updateGeometry();
  repaint();
}


void BarcodeWidget::paintEvent(QPaintEvent* event) {
  QPainter painter(this);
  if(d->m_barcode) {
    d->m_barcode->paint(&painter,QRectF(QPointF(0,0),size()));
    updateGeometry();
  } else {
    painter.fillRect(QRectF(QPointF(0,0),size()),Qt::black);
  }
  QWidget::paintEvent(event);
}

void BarcodeWidget::resizeEvent(QResizeEvent* event) {
  if(d->m_barcode) {
    updateGeometry();
    repaint();
  }
  QWidget::resizeEvent(event);
}

void BarcodeWidget::mousePressEvent(QMouseEvent* event) {
  if(d->m_barcode && event->buttons() & Qt::LeftButton) {
    QMimeData* data = new QMimeData();
    data->setImageData(d->m_barcode->toImage(size()));
    QDrag* drag = new QDrag(this);
    drag->setMimeData(data);
    drag->exec();
  } else {
    QWidget::mousePressEvent(event);
  }
}


QSize BarcodeWidget::minimumSizeHint() const
{
  if(d->m_barcode) {
    return d->m_barcode->minimumSize().toSize();
  } else {
    return QWidget::minimumSizeHint();
  }
}


prison::BarcodeWidget::~BarcodeWidget() {
  delete d->m_barcode;
  delete d;
}

void BarcodeWidget::setBarcode(AbstractBarcode* barcode) {
  delete d->m_barcode;
  d->m_barcode=barcode;
}


