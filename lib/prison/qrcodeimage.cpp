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

#include "qrcodeimage.h"

#include <qrencode.h>

#include <QDebug>

QImage prison::QRCodeImage(const QString& data, int size) {
  if(data.size()==0) {
    return QImage();
  }
  char* raw_string = qstrdup( data.toUtf8().trimmed().constData() );
  QRcode* code = QRcode_encodeString8bit(raw_string,0, QR_ECLEVEL_Q);
  free(raw_string);
  const int margin = 2;
  uchar* img = new uchar[4 /*32bit colors*/*sizeof(char*)*(2*margin + code->width)*(2*margin* + code->width)];
  uchar* p = img;
  const char white = 0xff;
  const char black = 0x00;
  for(int row = 0 ; row < code->width+2*margin ; row++) {
    for(int col = 0 ; col < code->width+2*margin ; col++) {
      if(row < margin || row >= (code->width+margin) || col < margin || col >= (code->width+margin)) {
        for(int i =0 ; i<4 /*4 bytes for color*/ ; i++) {
          *p = white;
          p++;
        }
      } else {
        int  c= (row-margin)*code->width + (col-margin);
        if(code->data[c] & (1<<0)) {
          for(int i =0 ; i<4 /*4 bytes for color*/ ; i++) {
            *p = black;
            p++;
          }
        } else {
          for(int i =0 ; i<4 /*4 bytes for color*/ ; i++) {
            *p = white;
            p++;
          }
        }
      }
    }
  }
  QImage tmp(img,code->width+2*margin,code->width+2*margin,QImage::Format_RGB32);
  QImage ret = tmp.convertToFormat(QImage::Format_Mono).scaled(tmp.width()*4,tmp.height()*4); //4 is determined by trial and error.
  free(img);
  QRcode_free(code);
  return ret;
}
