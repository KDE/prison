/*
    Copyright (c) 2010-2014 Sune Vuorela <sune@vuorela.dk>

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

#include "barcodeexamplewidget.h"
#include "src/lib/abstractbarcode.h"
#include <QResizeEvent>
#include <QPainter>
#include <QMimeData>
#include <QDrag>

using namespace Prison;

BarcodeExampleWidget::BarcodeExampleWidget(AbstractBarcode* barcode, QWidget* parent): QWidget(parent), m_barcode(barcode)
{

}



void BarcodeExampleWidget::setData(const QString &data) {
  if(m_barcode)
    m_barcode->setData(data);
  updateGeometry();
  repaint();
}


void BarcodeExampleWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if(m_barcode) {
        QRect targetrect = rect();
        QImage image = m_barcode->toImage(targetrect.size());
        if (!image.isNull()) {
            QRectF rect(targetrect.left() + targetrect.width() /2 - image.size().width() /2,
                        targetrect.top() + targetrect.height()/2 - image.size().height()/2,
                        targetrect.size().width(),
                        targetrect.height());
            painter.drawImage(rect.topLeft(), image, image.rect());
        } else {
            painter.fillRect(QRectF(QPointF(0,0),size()),Qt::cyan);
        }
    } else {
        painter.fillRect(QRectF(QPointF(0,0),size()),Qt::black);
    }
    QWidget::paintEvent(event);
}

void BarcodeExampleWidget::resizeEvent(QResizeEvent* event) {
  if(m_barcode) {
    updateGeometry();
    repaint();
  }
  QWidget::resizeEvent(event);
}

void BarcodeExampleWidget::mousePressEvent(QMouseEvent* event) {
  if(m_barcode && event->buttons() & Qt::LeftButton) {
    QMimeData* data = new QMimeData();
    data->setImageData(m_barcode->toImage(rect().size()));
    QDrag* drag = new QDrag(this);
    drag->setMimeData(data);
    drag->exec();
  } else {
    QWidget::mousePressEvent(event);
  }
}


QSize BarcodeExampleWidget::minimumSizeHint() const
{
  if(m_barcode) {
    return m_barcode->minimumSize().toSize();
  } else {
    return QWidget::minimumSizeHint();
  }
}


BarcodeExampleWidget::~BarcodeExampleWidget()
{
  delete m_barcode;
}
