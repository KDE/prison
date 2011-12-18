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

#ifndef PRISON_CODE39BARCODE_H
#define PRISON_CODE39BARCODE_H

#include <prison/abstractbarcode.h>

namespace prison {
  /**
   * Code 39 Barcode generator
   */
class PRISON_EXPORT Code39Barcode : public prison::AbstractBarcode {
  public:
    /**
     * creates a Code 39 generator
     */
    Code39Barcode();
    virtual ~Code39Barcode();
    /**
     * This function generates the barcode
     * @return QImage containing a barcode, trying to approximate the requested sizes
     * @param size The requested size of the barcode, approximate. if the barcode generator can't get the data to fit in there, it might be larger
     */
    virtual QImage toImage(const QSizeF& size);
  private:
    class Private;
    Private *d;
};
}; // namespace

#endif // PRISON_CODE39BARCODE_H
