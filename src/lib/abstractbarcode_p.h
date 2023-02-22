/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_ABSTRACTBARCODE_P_H
#define PRISON_ABSTRACTBARCODE_P_H

#include "abstractbarcode.h"

#include <QVariant>

namespace Prison
{
class AbstractBarcode;

class AbstractBarcodePrivate
{
public:
    explicit AbstractBarcodePrivate(AbstractBarcode *barcode);
    bool isEmpty() const;
    bool sizeTooSmall(const QSizeF &size) const;
    void recompute();

    QVariant m_data;
    QImage m_cache;
    QColor m_foreground = Qt::black;
    QColor m_background = Qt::white;
    AbstractBarcode::Dimensions m_dimension = AbstractBarcode::NoDimensions;
    AbstractBarcode *q;
};

}

#endif
