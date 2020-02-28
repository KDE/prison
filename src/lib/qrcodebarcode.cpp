/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "qrcodebarcode.h"
#include <qrencode.h>
#include <QColor>

using namespace Prison;

QRCodeBarcode::QRCodeBarcode() = default;
QRCodeBarcode::~QRCodeBarcode() = default;

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
