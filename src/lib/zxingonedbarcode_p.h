/*
    SPDX-FileCopyrightText: 2023 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_ZXINGONEDBARCODE_H
#define PRISON_ZXINGONEDBARCODE_H

#include "abstractbarcode.h"
#include "zxingutil_p.h"

#include <QVariant>

#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>

#include <stdexcept>

namespace Prison
{
/** Generic support for ZXing 1D barcodes. */
template<ZXing::BarcodeFormat Format>
class ZXingOneDBarcode : public AbstractBarcode
{
public:
    explicit inline ZXingOneDBarcode()
        : AbstractBarcode(AbstractBarcode::OneDimension)
    {
    }

protected:
    inline QImage paintImage(const QSizeF &) override
    {
        try {
            ZXing::MultiFormatWriter writer(Format);
            const auto matrix = writer.encode(ZXingUtil::toStdWString(data().isEmpty() ? QVariant(byteArrayData()) : QVariant(data())), 1, 1);
            return ZXingUtil::toImage(matrix, foregroundColor(), backgroundColor());
        } catch (const std::invalid_argument &e) {
        }; // input too large or incompatible
        return {};
    }
};

}

#endif // PRISON_PDF417BARCODE_H
