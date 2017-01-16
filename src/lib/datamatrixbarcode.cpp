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

#include "datamatrixbarcode.h"
#include <dmtx.h>
#include <QColor>
using namespace Prison;

/**
 * @cond PRIVATE
 */
class DataMatrixBarcode::Private {
  public:
};
/**
 * @endcond
 */

DataMatrixBarcode::DataMatrixBarcode() : d(nullptr) {

}

DataMatrixBarcode::~DataMatrixBarcode() {
  delete d;
}


QImage DataMatrixBarcode::paintImage(const QSizeF& size) {
  const int width = qRound(qMin(size.width(),size.height()));
  if(data().size()==0 || width == 0 || data().size() > 1200) {
    return QImage();
  }

  DmtxEncode * enc = dmtxEncodeCreate();
  dmtxEncodeSetProp( enc, DmtxPropPixelPacking, DmtxPack32bppRGBX );
  dmtxEncodeSetProp( enc, DmtxPropWidth, width );
  dmtxEncodeSetProp( enc, DmtxPropHeight, width );

  QByteArray trimmedData(data().trimmed().toUtf8());
  DmtxPassFail result =  dmtxEncodeDataMatrix(enc, trimmedData.length(),
                                              reinterpret_cast<unsigned char*>(trimmedData.data()));
  if(result == DmtxFail) {
    dmtxEncodeDestroy(&enc);
    return QImage();
  }
  Q_ASSERT(enc->image->width == enc->image->height);

  setMinimumSize(QSizeF(enc->image->width,enc->image->height));
  QImage ret;

  if(foregroundColor()==Qt::black && backgroundColor() == Qt::white) {
    QImage tmp(enc->image->pxl,enc->image->width,enc->image->height, QImage::Format_ARGB32);
    //we need to copy, because QImage generated from a char pointer requires the
    //char pointer to be kept around forever, and manually deleted.
    ret=tmp.copy();
  } else {
    if(enc->image->width>0) {
      int size = enc->image->width*enc->image->height*4;
      uchar* img = new uchar[size];
      QByteArray background;
      background[3] = qAlpha(backgroundColor().rgba());
      background[2] = qRed(backgroundColor().rgba());
      background[1] = qGreen(backgroundColor().rgba());
      background[0] = qBlue(backgroundColor().rgba());
      QByteArray foreground = new char[4];
      foreground[3] = qAlpha(foregroundColor().rgba());
      foreground[2] = qRed(foregroundColor().rgba());
      foreground[1] = qGreen(foregroundColor().rgba());
      foreground[0] = qBlue(foregroundColor().rgba());
      for(int i = 1 ; i < size; i+=4) {
	QByteArray color;
	if(enc->image->pxl[i]==0x00) {
	  color = foreground;
	} else {
	  color = background;
	}
	for(int j = 0 ; j < 4 ; j++) {
	  img[i-1+j] = color[j];
	}
      }
      QImage tmp(img,enc->image->width,enc->image->height, QImage::Format_ARGB32);
      //we need to copy, because QImage generated from a char pointer requires the
      //char pointer to be kept around forever, and manually deleted.
      ret=tmp.copy();
      delete[] img;
    }
  }
  if(!ret.isNull() && ret.width() < width) {
    ret = ret.scaled(width,width);
  }
  dmtxEncodeDestroy(&enc);
  return ret;
}
