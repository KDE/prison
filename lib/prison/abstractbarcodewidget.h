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

#ifndef PRISON_ABSTRACTBARCODEWIDGET_H
#define PRISON_ABSTRACTBARCODEWIDGET_H

#include <QWidget>
#include "prison_export.h"

namespace prison {

class PRISON_EXPORT AbstractBarcodeWidget : public QWidget {
  public:
    /**
     * reimpl
     */
    AbstractBarcodeWidget(QWidget* parent = 0, Qt::WindowFlags f = 0);
    virtual ~AbstractBarcodeWidget();
    /**
     * sets the data to be shown on the barcode
     */
    void setData(const QString& data);
    /**
     * retrieved the text from the barcode
     */
    const QString& data() const;
    
  protected:
    /**
     * Updates the image cache when data is changed
     * or when the widget is resized.
     * This function is the one to implement to add
     * support for new formats.
     */
    virtual QPixmap redoImage()=0;
    /**
     * reimpl
     */
    virtual void resizeEvent(QResizeEvent* event );
    /**
     * reimpl
     */
    virtual void paintEvent(QPaintEvent* event );
    /**
     * the preferred width of a image.
     */
    const QSize& imageSize() const;

  private:
    class Private;
    Private* d;
};

}; //namespcae

#endif // PRISON_ABSTRACTBARCODEWIDGET_H
