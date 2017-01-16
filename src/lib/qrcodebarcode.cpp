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

#include "qrcodebarcode.h"
#include <qrencode.h>
#include <QColor>

using namespace Prison;
/**
@cond PRIVATE
*/
class QRCodeBarcode::Private {
  public:
};
/**
@endcond
*/

QRCodeBarcode::QRCodeBarcode() : AbstractBarcode(), d(nullptr){
  
}

QRCodeBarcode::~QRCodeBarcode() {
  delete d;
}



QImage QRCodeBarcode::paintImage(const QSizeF& size) {
  const int width = qRound(qMin(size.width(),size.height()));
  if(data().size()==0 || width==0) {
    return QImage();
  }
  const QByteArray trimmedData(data().trimmed().toUtf8());
  QRcode* code = QRcode_encodeString8bit(trimmedData.constData(), 0, QR_ECLEVEL_Q);
  if(!code) {
    return QImage();
  }
  const int margin = 2;
  /*32 bit colors, 8 bit pr byte*/
  uchar* img = new uchar[4 *sizeof(char*)*(2*margin + code->width)*(2*margin* + code->width)];
  uchar* p = img;
  QByteArray background;
  background[3] = qAlpha(backgroundColor().rgba());
  background[2] = qRed(backgroundColor().rgba());
  background[1] = qGreen(backgroundColor().rgba());
  background[0] = qBlue(backgroundColor().rgba());
  QByteArray foreground;
  foreground[3] = qAlpha(foregroundColor().rgba());
  foreground[2] = qRed(foregroundColor().rgba());
  foreground[1] = qGreen(foregroundColor().rgba());
  foreground[0] = qBlue(foregroundColor().rgba());
  for(int row = 0 ; row < code->width+2*margin ; row++) {
    for(int col = 0 ; col < code->width+2*margin ; col++) {
      if(row < margin || row >= (code->width+margin) || col < margin || col >= (code->width+margin)) {
        /*4 bytes for color*/
        for(int i =0 ; i<4 ; i++) {
          *p = background[i];
          p++;
        }
      } else {
        int  c= (row-margin)*code->width + (col-margin);
        /*it is bit 1 that is the interesting bit for us from libqrencode*/
        if(code->data[c] & 1) {
          /*4 bytes for color*/
          for(int i =0 ; i<4 ; i++) {
            *p = foreground[i];
            p++;
          }
        } else {
          /*4 bytes for color*/
          for(int i =0 ; i<4 ; i++) {
            *p = background[i];
            p++;
          }
        }
      }
    }
  }
  QImage tmp(img,code->width+2*margin,code->width+2*margin,QImage::Format_ARGB32);
  setMinimumSize(QSizeF(tmp.width()*4,tmp.height()*4));
  QImage ret = tmp.convertToFormat(QImage::Format_ARGB32).scaled(qMax(tmp.width()*4,width),qMax(tmp.height()*4,width)); //4 is determined by trial and error.
  delete[] img;
  QRcode_free(code);
  return ret;
}
