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

class QColor;
class QPainter;

namespace prison {
  /**
   * base class for barcode generators
   * To add your own barcode generator, subclass this class
   * and reimplement toImage(const QSizeF&) to do the actual
   * work of generating the barcode.
   *
   * The barcode is cached in AbstractBarcode when painting and
   * the size and the data doesn't change. Using the same AbstractBarcode
   * to paint on several surfaces, if they aren't of the exact same size
   * will break the caching
   */
class PRISON_EXPORT AbstractBarcode {
  public:
    /**
     * creates a barcode generator without any data
     */
    AbstractBarcode();
    virtual ~AbstractBarcode();
    /**
     * @return the QString encoded in this barcode.
     */
    QString data() const;
    /**
     * sets the data to be drawn by this function
     * calling this function does not do any repaints of anything, they are
     * your own responsibility. If you are using the barcodes thru BarcodeWidget or BarcodeItem, you
     * should rather use their setData function, as they handle the relevant updates.
     * @param data QString containing the data
     */
    void setData(const QString& data);
    /**
     * paints the barcode in the given rectangle.
     * @param painter The QPainter to paint upon
     * @param targetrect The rectangle to paint within
     */
    void paint(QPainter* painter, const QRectF& targetrect);
    /**
     * Creates a image with a barcode on
     * This is the function that actually does all the interesting things, the rest is just icing and api.
     * @return QImage with a barcode on, trying to match the requested size
     * @param size Requested size for the barcode, if smaller than minimumSize, a image fitting within minimumsize will be  returned
     */
    virtual QImage toImage(const QSizeF& size) = 0 ;
    /**
     * Note! minimalSize() doesn't work as expected if this is not painting on something.
     * @return the minimal size for this barcode.
     */
    QSizeF minimumSize() const;
    /**
     * @return the foreground color (by default black) to be used for the barcode.
     */
    const QColor& foregroundColor() const;
    /**
     * @return the background color (by default white) to be used for the barcode.
     */
    const QColor& backgroundColor() const;
    /**
     * sets the foreground color
     * @param foregroundcolor - the new foreground color
     */
    void setForegroundColor(const QColor& foregroundcolor);
    /**
     * sets the background color
     * @param backgroundcolor - the new background color
     */
    void setBackgroundColor(const QColor& backgroundcolor);

  protected:
    /**
     * Sets the minimum size for this barcode.
     * Some barcodes have minimum sizes for when they are readable and such
     * @param minimumSize QSizeF holding the minimum size for this barcode
     */
    void setMinimumSize(const QSizeF& minimumSize);
  private:
   class Private;
   /**
    * d-pointer
    */
   Private* d;
   
};
} //namespace

#endif // PRISON_ABSTRACTBARCODE_H
