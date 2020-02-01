/*
    SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
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
    const auto img = m_barcode->toImage(QSizeF(w_max, h_max));
    const auto x = (w_max - img.width()) / 2;
    const auto y = (h_max - img.height()) / 2;
    painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
    painter->drawImage(QRectF(x, y, img.width(), img.height()), img, img.rect());
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
