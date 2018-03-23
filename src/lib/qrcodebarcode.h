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

#ifndef PRISON_QRCODEBARCODE_H
#define PRISON_QRCODEBARCODE_H

#include "abstractbarcode.h"

namespace Prison {
  /**
   * QRCode Barcode generator ; uses libqrencode to do the actual encoding
   * of the barcode.
   */
class PRISON_EXPORT QRCodeBarcode : public Prison::AbstractBarcode {
  public:
    /**
     * creates a QRCode generator
     */
    QRCodeBarcode();
    ~QRCodeBarcode() override;
    /**
     * This is the function doing the actual work in generating the barcode
     * @return QImage containing a QRCode, trying to approximate the requested sizes
     * @param size The requested size of the barcode, approximate. if the barcode generator can't get the data to fit in there, it might be a null QImage
     */
    QImage paintImage(const QSizeF& size) override;
  private:
    class Private;
    Private *d;
};
} // namespace 

#endif // PRISON_QRCODEBARCODE_H
