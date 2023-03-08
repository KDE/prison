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
    explicit inline AbstractBarcodePrivate(AbstractBarcode::Dimensions dim)
        : m_dimension(dim)
    {
    }
    virtual ~AbstractBarcodePrivate() = default;

    /**
     * Doing the actual painting of the image
     * @param size unused - will be removed in KF6
     * @return image with barcode, or null image
     */
    // TODO KF6: remove the size argument
    virtual QImage paintImage(const QSizeF &size) = 0;

    static inline AbstractBarcode *makeBarcode(AbstractBarcodePrivate *dd)
    {
        return new AbstractBarcode(dd);
    }

    bool isEmpty() const;
    bool sizeTooSmall(const QSizeF &size) const;
    void recompute();

    QVariant m_data;
    QImage m_cache;
    QColor m_foreground = Qt::black;
    QColor m_background = Qt::white;
    AbstractBarcode::Dimensions m_dimension = AbstractBarcode::NoDimensions;
    AbstractBarcode *q = nullptr;
};

}

#endif
