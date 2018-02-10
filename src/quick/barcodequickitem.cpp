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

#include "barcodequickitem.h"

#include <prison/prison.h>

#include <QDebug>
#include <QPainter>

using namespace Prison;

BarcodeQuickItem::BarcodeQuickItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

BarcodeQuickItem::~BarcodeQuickItem() = default;

QString BarcodeQuickItem::content() const
{
    return m_content;
}

void BarcodeQuickItem::setContent(const QString& content)
{
    if (m_content == content)
        return;
    m_content = content;
    emit contentChanged();
    updateBarcode();
}

BarcodeQuickItem::BarcodeType BarcodeQuickItem::barcodeType() const
{
    return static_cast<BarcodeType>(m_type);
}

void BarcodeQuickItem::setBarcodeType(BarcodeQuickItem::BarcodeType type)
{
    if (m_type == static_cast<Prison::BarcodeType>(type))
        return;
    m_type = static_cast<Prison::BarcodeType>(type);
    emit barcodeTypeChanged();
    m_barcode.reset();
    updateBarcode();
}

QColor BarcodeQuickItem::foregroundColor() const
{
    return m_fgColor;
}

void BarcodeQuickItem::setForegroundColor(const QColor &color)
{
    if (m_fgColor == color)
        return;
    m_fgColor = color;
    emit foregroundColorChanged();
    updateBarcode();
}

QColor BarcodeQuickItem::backgroundColor() const
{
    return m_bgColor;
}

void BarcodeQuickItem::setBackgroundColor(const QColor &color)
{
    if (m_bgColor == color)
        return;
    m_bgColor = color;
    emit backgroundColorChanged();
    updateBarcode();
}

void BarcodeQuickItem::paint(QPainter* painter)
{
    if (!m_barcode)
        return;

    const auto w_max = std::max(implicitWidth(), width());
    const auto h_max = std::max(implicitHeight(), height());
    const auto scale = std::min(w_max / implicitWidth(), h_max / implicitHeight());
    const auto w = scale * implicitWidth();
    const auto h = scale * implicitHeight();
    const auto x = (width() - w) / 2;
    const auto y = (height() - h) / 2;

    const auto img = m_barcode->toImage(m_barcode->minimumSize());
    painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter->drawImage(QRectF(x, y, w, h), img, img.rect());
}

void BarcodeQuickItem::componentComplete()
{
    QQuickPaintedItem::componentComplete();
    updateBarcode();
}

void BarcodeQuickItem::updateBarcode()
{
    if (!isComponentComplete())
        return;

    if (m_type == Prison::Null || m_content.isEmpty()) {
        m_barcode.reset();
        update();
        return;
    }

    if (!m_barcode)
        m_barcode.reset(Prison::createBarcode(m_type));
    if (m_barcode) {
        m_barcode->setData(m_content);
        m_barcode->setForegroundColor(m_fgColor);
        m_barcode->setBackgroundColor(m_bgColor);
        // minimumSize() is only providing valid results after the first call to toImage()...
        m_barcode->toImage(m_barcode->minimumSize());
        setImplicitSize(m_barcode->minimumSize().width(), m_barcode->minimumSize().height());
    }

    update();
}
