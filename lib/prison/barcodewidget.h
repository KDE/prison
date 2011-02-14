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

#ifndef PRISON_BARCODEWIDGET_H
#define PRISON_BARCODEWIDGET_H

#include <QWidget>
#include <prison/prison_export.h>


namespace prison {
class AbstractBarcode;
/**
 * QWidget with a barcode on
 */

class PRISON_EXPORT BarcodeWidget : public QWidget {
  public:
    /**
     * Creates a barcodewidget with no barcode generator
     * use setBarcode() to set the barcode
     * @param parent the parent in QWidget hierachy
     */
    BarcodeWidget(QWidget* parent=0);
    /**
     * Creates a barcode widget with 'barcode' as barcode generator
     * @param barcode The barcode generator for this widget. Takes ownership over the barcode generator
     * @param parent the parent in QWidget hierachy
     */
    BarcodeWidget(AbstractBarcode* barcode, QWidget* parent=0);
    virtual ~BarcodeWidget();
    /**
     * sets the data shown to data, and triggers a repaint and resize if needed
     * @param data QString holding the data to be shown
     */
    void setData(QString data);
    /**
     * sets the barcode generator to barcode, and deletes the existing barcode.
     * @param barcode USes this barcode generator for this widget, and takes ownership over it
     */
    void setBarcode(AbstractBarcode* barcode);
    /**
     * Reimplementation
     * @return minimumSizeHint for this widget
     */
    virtual QSize minimumSizeHint() const;
  protected:
    /**
     * paintEvent
     * @param event QPaintEvent
     */
    virtual void paintEvent(QPaintEvent* event );
    /**
     * resizeEvent
     * @param event QResizeEvent
     */
    virtual void resizeEvent(QResizeEvent* event );
    /**
     * enables drag from the barcodewidget
     * @param event QMouseEvent
     */
    virtual void mousePressEvent(QMouseEvent* event);
  private:
    class Private;
    /**
     * d pointer
     */
    Private* d;
};
}; //namespace 

#endif // PRISON_BARCODEWIDGET_H
