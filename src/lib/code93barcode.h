/*
    Copyright (c) 2011 Geoffry Song <goffrie@gmail.com>

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

#ifndef PRISON_CODE93BARCODE_H
#define PRISON_CODE93BARCODE_H

#include "abstractbarcode.h"

namespace Prison {
  /**
   * Code 93 Barcode generator
   */
class Code93Barcode : public Prison::AbstractBarcode {
  public:
    /**
     * creates a Code 93 generator
     */
    Code93Barcode();
    ~Code93Barcode() override;
    /**
     * This function generates the barcode
     * @return QImage containing a barcode, trying to approximate the requested sizes
     * @param size The requested size of the barcode, approximate. if the barcode generator can't generate it, it can return a null QImage
     */
    QImage paintImage(const QSizeF& size) override;
  private:
    class Private;
    Private *d;
};
} // namespace

#endif // PRISON_CODE39BARCODE_H
