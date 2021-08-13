/*
    SPDX-FileCopyrightText: 2010-2014 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "barcodeexamplewidget.h"
// Prison
#include <prison/abstractbarcode.h>
// Qt
#include <QDrag>
#include <QGuiApplication>
#include <QMimeData>
#include <QPainter>
#include <QResizeEvent>
#include <QScreen>

using namespace Prison;

BarcodeExampleWidget::BarcodeExampleWidget(AbstractBarcode *barcode, QWidget *parent)
    : QWidget(parent)
    , m_barcode(barcode)
{
}

void BarcodeExampleWidget::setData(const QString &data)
{
    if (m_barcode) {
        m_barcode->setData(data);
    }
    updateGeometry();
    repaint();
}

void BarcodeExampleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (m_barcode) {
        QRect targetrect = rect();
        QImage image = m_barcode->toImage(targetrect.size());
        if (!image.isNull()) {
            QRectF rect(targetrect.left() + targetrect.width() / 2 - image.size().width() / 2,
                        targetrect.top() + targetrect.height() / 2 - image.size().height() / 2,
                        targetrect.size().width(),
                        targetrect.height());
            painter.drawImage(rect.topLeft(), image, image.rect());
        } else {
            painter.fillRect(QRectF(QPointF(0, 0), size()), Qt::cyan);
        }
    } else {
        painter.fillRect(QRectF(QPointF(0, 0), size()), Qt::black);
    }
    QWidget::paintEvent(event);
}

void BarcodeExampleWidget::resizeEvent(QResizeEvent *event)
{
    if (m_barcode) {
        updateGeometry();
        repaint();
    }
    QWidget::resizeEvent(event);
}

void BarcodeExampleWidget::mousePressEvent(QMouseEvent *event)
{
    if (m_barcode && event->buttons() & Qt::LeftButton) {
        QMimeData *data = new QMimeData();
        data->setImageData(m_barcode->toImage(rect().size()));
        QDrag *drag = new QDrag(this);
        drag->setMimeData(data);
        drag->exec();
    } else {
        QWidget::mousePressEvent(event);
    }
}

QSize BarcodeExampleWidget::minimumSizeHint() const
{
    if (m_barcode) {
        return m_barcode->preferredSize(QGuiApplication::primaryScreen()->devicePixelRatio()).toSize();
    } else {
        return QWidget::minimumSizeHint();
    }
}

BarcodeExampleWidget::~BarcodeExampleWidget()
{
    delete m_barcode;
}
