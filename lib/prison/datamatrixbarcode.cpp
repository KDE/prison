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

#include "datamatrixbarcode.h"
#include <dmtx.h>
using namespace prison;

/**
 * @cond PRIVATE
 */
class DataMatrixBarcode::Private {
  public:
};
/**
 * @endcond
 */

DataMatrixBarcode::DataMatrixBarcode() : d(0) {

}

DataMatrixBarcode::~DataMatrixBarcode() {
  delete d;
}


QImage DataMatrixBarcode::toImage(const QSizeF& size) {
  const int width = qRound(qMin(size.width(),size.height()));
  if(data().size()==0 || width == 0) {
    return QImage();
  }
  
  DmtxEncode * enc = dmtxEncodeCreate();
  dmtxEncodeSetProp( enc, DmtxPropPixelPacking, DmtxPack32bppRGBX );
  dmtxEncodeSetProp( enc, DmtxPropWidth, width );
  dmtxEncodeSetProp( enc, DmtxPropHeight, width );

  QByteArray trimmedData(data().trimmed().toUtf8());
  dmtxEncodeDataMatrix(enc, trimmedData.length(),
                       reinterpret_cast<unsigned char*>(trimmedData.data()));
  Q_ASSERT(enc->image->width == enc->image->height);
  
  setMinimumSize(QSizeF(enc->image->width,enc->image->height));
  
  QImage tmp(enc->image->pxl,enc->image->width,enc->image->height, QImage::Format_RGB32);
  //we need to copy, because QImage generated from a char pointer requires the
  //char pointer to be kept around forever, and manually deleted.
  QImage ret=tmp.convertToFormat(QImage::Format_Mono);
  if(ret.width() < width) {
    ret = ret.scaled(width,width);
  }
  dmtxEncodeDestroy(&enc);
  return ret;
}
