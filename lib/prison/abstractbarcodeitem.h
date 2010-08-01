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

#ifndef PRISON_ABSTRACTBARCODEITEM_H
#define PRISON_ABSTRACTBARCODEITEM_H

#include <QGraphicsItem>
#include "prison_export.h"


namespace prison {

class PRISON_EXPORT AbstractBarcodeItem : public QGraphicsItem {
  public:
    /**
     * reimpl
     */
    AbstractBarcodeItem(QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
    virtual ~AbstractBarcodeItem();
    /**
     * reimpl
     */
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    /**
     * reimpl
     */
    virtual QRectF boundingRect() const;
    /**
     * returns the data (QString) to show on the barcode
     */
    const QString& data() const;
    /**
     * Sets the data to be shown on the barcode
     * @param data
     */
    void setData(const QString& data);
    
  protected:
    /**
     * the preferred size of the image. Currently, images are quadratic.
     */
    qreal imageWidth() const;
    /**
     * This function is called when data is changed
     * and redos the actual image. This is the function
     * to reimplement to add support new barcode formats.
     */
    virtual QPixmap redoImage() = 0;
    
  private:
    class Private;
    Private *d;
};

}

#endif // PRISON_ABSTRACTBARCODEITEM_H
