/*
    Copyright (c) 2018 Volker Krause <vkrause@kde.org>

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

#ifndef PRISON_BARCODEQUICKITEM_H
#define PRISON_BARCODEQUICKITEM_H

#include <prison/prison.h>

#include <QColor>
#include <QQuickPaintedItem>

#include <memory>

namespace Prison {

class AbstractBarcode;

class BarcodeQuickItem : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(BarcodeType barcodeType READ barcodeType WRITE setBarcodeType NOTIFY barcodeTypeChanged)
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    enum BarcodeType {
        Null = Prison::Null,
        QRCode = Prison::QRCode,
        DataMatrix = Prison::DataMatrix,
        Aztec = Prison::Aztec,
        Code39 = Prison::Code39,
        Code93 = Prison::Code93
    };
    Q_ENUM(BarcodeType)
    explicit BarcodeQuickItem(QQuickItem *parent = nullptr);
    ~BarcodeQuickItem();

    QString content() const;
    void setContent(const QString &data);

    Prison::BarcodeQuickItem::BarcodeType barcodeType() const;
    void setBarcodeType(Prison::BarcodeQuickItem::BarcodeType type);

    QColor foregroundColor() const;
    void setForegroundColor(const QColor &color);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    void paint(QPainter *painter) override;
    void componentComplete() override;

Q_SIGNALS:
    void contentChanged();
    void barcodeTypeChanged();
    void foregroundColorChanged();
    void backgroundColorChanged();

private:
    void updateBarcode();

    QString m_content;
    std::unique_ptr<AbstractBarcode> m_barcode;
    QColor m_fgColor = Qt::black;
    QColor m_bgColor = Qt::white;
    Prison::BarcodeType m_type = Prison::Null;
};

}

#endif // PRISON_BARCODEQUICKITEM_H
