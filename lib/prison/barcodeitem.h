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

#ifndef PRISON_BARCODEITEM_H
#define PRISON_BARCODEITEM_H

#include <QGraphicsItem>
#include <prison/prison_export.h>

namespace prison {

class AbstractBarcode;

class PRISON_EXPORT BarcodeItem : public QGraphicsItem {
  public:
    /**
     * Creates a barcodeitem without a barcode generator, and parent as parent
     * use setBarcode() to set a barcode generator
     */
    BarcodeItem(QGraphicsItem* parent=0);
    /**
     * creates a barcode item with barcode as barcode generator, and parent as parent
     * This function takes ownership over the barcode
     */
    BarcodeItem(prison::AbstractBarcode* barcode, QGraphicsItem* parent=0);
    virtual ~BarcodeItem();
    /**
     * sets the data on the barcode to data
     */
    void setData(const QString& data);
    /**
     * sets the barcode generator to barcode, and deletes the existing barcode generator if exists.
     * This function takes ownership over the barcode generator
     */
    void setBarcode(prison::AbstractBarcode* barcode);
    /**
     * \reimpl
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    /**
     * \reimpl
     */
    virtual QRectF boundingRect() const;
  private:
    class Private;
    Private* d;
};
}; //namespace

#endif // PRISON_BARCODEITEM_H
