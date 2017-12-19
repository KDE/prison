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

#ifndef PRISON_BARCODEWIDGET_H
#define PRISON_BARCODEWIDGET_H

#include <QWidget>

namespace Prison {
    class AbstractBarcode;
}
/**
 * QWidget with a barcode on
 */
class BarcodeExampleWidget : public QWidget {
  public:
    /**
     * Creates a barcode widget with 'barcode' as barcode generator
     * @param barcode The barcode generator for this widget. Takes ownership over the barcode generator
     * @param parent the parent in QWidget hierachy
     */
    BarcodeExampleWidget(Prison::AbstractBarcode* barcode, QWidget* parent=nullptr);
    virtual ~BarcodeExampleWidget();
    /**
     * sets the data shown to data, and triggers a repaint and resize if needed
     * @param data QString holding the data to be shown
     */
    void setData(const QString &data);
    /**
     * Reimplementation
     * @return minimumSizeHint for this widget
     */
    QSize minimumSizeHint() const override;
  protected:
    /**
     * paintEvent
     * @param event QPaintEvent
     */
    void paintEvent(QPaintEvent* event ) override;
    /**
     * resizeEvent
     * @param event QResizeEvent
     */
    void resizeEvent(QResizeEvent* event ) override;
    /**
     * enables drag from the barcodewidget
     * @param event QMouseEvent
     */
    void mousePressEvent(QMouseEvent* event) override;
  private:
    Prison::AbstractBarcode* m_barcode;
};

#endif // PRISON_BARCODEWIDGET_H
