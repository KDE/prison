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

#include "qrcodewidget.h"
#include "qrcodeimage.h"

#include <QPixmap>

using namespace prison;

QRCodeWidget::QRCodeWidget(QWidget* parent, Qt::WindowFlags f): AbstractBarcodeWidget(parent, f) {

}

QRCodeWidget::~QRCodeWidget() {

}

QPixmap QRCodeWidget::redoImage() {
  QImage tmp =  prison::QRCodeImage(data(),imageWidth());
  if(tmp.isNull()) {
    return QPixmap();
  }
  int scale = (int)(imageWidth()/tmp.size().width());
  QPixmap ret;
  if(scale < 1 ) {
    ret = QPixmap::fromImage(tmp);
  } else {
    ret = QPixmap::fromImage(tmp.scaled((tmp.size().width())*scale,(tmp.size().width())*scale));
  }
  QSize minimum_size = QSize(qMax(tmp.width(),10),qMax(tmp.height(),10));
  if(minimum_size!= minimumSize()) {
    setMinimumSize(minimum_size);
    updateGeometry();
  }
  return ret;
}

