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

class PRISON_EXPORT BarcodeWidget : public QWidget {
  public:
    BarcodeWidget(QWidget* parent=0);
    /**
     * Creates a barcode widget with 'barcode' as barcode generator
     * Takes ownership over the barcode generator
     */
    BarcodeWidget(AbstractBarcode* barcode, QWidget* parent=0);
    virtual ~BarcodeWidget();
    void setData(QString data);
    virtual QSize minimumSizeHint() const;
  protected:
    virtual void paintEvent(QPaintEvent* event );
    virtual void resizeEvent(QResizeEvent* );
    virtual void mousePressEvent(QMouseEvent* event);
  private:
    class Private;
    Private* d;
};
}; //namespace 

#endif // PRISON_BARCODEWIDGET_H
