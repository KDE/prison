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

#include "abstractbarcodewidget.h"

#include <QImage>
#include <QResizeEvent>
#include <QPaintEvent>
#include <qpainter.h>

#include <QDebug>

class prison::AbstractBarcodeWidget::Private {
  public:
    QString data;
    bool dirty;
    QPixmap cache;
    QSize size;
    Private() { dirty = true;
                size=QSize(10,10); }
};

prison::AbstractBarcodeWidget::AbstractBarcodeWidget(QWidget* parent, Qt::WindowFlags f): QWidget(parent, f), d(new AbstractBarcodeWidget::Private) {
  setMinimumSize(10,10);
}

prison::AbstractBarcodeWidget::~AbstractBarcodeWidget() {

}

const QString& prison::AbstractBarcodeWidget::data() const {
  return d->data;
}

void prison::AbstractBarcodeWidget::setData(const QString& data) {
  d->data=data;
  d->dirty=true;
  repaint();
}

void prison::AbstractBarcodeWidget::resizeEvent(QResizeEvent* event) {
  QSize newsize = event->size();
  if(newsize!=d->size) {
    d->size=newsize;
    d->dirty=true;
  }
  QWidget::resizeEvent(event);
}

void prison::AbstractBarcodeWidget::paintEvent(QPaintEvent* event) {
  if(d->dirty) {
    d->cache = updateImage();
    d->dirty = false;
  }
  if(!d->cache.isNull()) {
    QPainter painter(this);
    QSize currentsize = size();
    int xoffset = (currentsize.width()-d->cache.size().width())/2;
    int yoffset = (currentsize.height()-d->cache.size().height())/2;
    painter.drawPixmap(QPoint(xoffset,yoffset),d->cache,d->cache.rect());
  }
 // QWidget::paintEvent(event);
}

const QSize& prison::AbstractBarcodeWidget::imageSize() const {
  return d->size;
}
