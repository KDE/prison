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

#ifndef PRISON_ABSTRACTBARCODE_H
#define PRISON_ABSTRACTBARCODE_H
#include <QString>
#include <QSizeF>
#include <QImage>

#include <prison/prison_export.h>

class QPainter;

namespace prison {
class PRISON_EXPORT AbstractBarcode {
  public:
    /**
     * creates a barcode generator without any data
     */
    AbstractBarcode();
    virtual ~AbstractBarcode();
    /**
     * returns the QString encoded in this barcode.
     */
    QString data() const;
    /**
     * sets the data to be drawn by this function
     */
    void setData(const QString& data);
    /**
     * paints the barcode at the given position.
     */
    void paint(QPainter* painter, const QRectF& targetrect);
    /**
     * Creates a image with a barcode on
     * This is the function that actually does all the interesting things, the rest is just icing and api.
     */
    virtual QImage toImage(const QSizeF& size) = 0 ;
    /**
     * returns the minimal size for this barcode.
     */
    QSizeF minimumSize() const;
  protected:
    /**
     * Sets the minimum size for this barcode.
     * Some barcodes have minimum sizes for when they are readable and such
     */
    void setMinimumSize(const QSizeF& minimumSize);
  private:
   class Private;
   Private* d;
   
};
}; //namespace

#endif // PRISON_ABSTRACTBARCODE_H
