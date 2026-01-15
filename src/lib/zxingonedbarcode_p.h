/*
    SPDX-FileCopyrightText: 2023 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_ZXINGONEDBARCODE_H
#define PRISON_ZXINGONEDBARCODE_H

#include "config-prison.h"

#include "abstractbarcode_p.h"
#include "zxingutil_p.h"

#if KZXING_VERSION < KZXING_VERSION_CHECK(3, 0, 0)
#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>
#else
#include <ZXing/CreateBarcode.h>
#include <ZXing/WriteBarcode.h>
#endif

#include <stdexcept>

namespace Prison
{
/*!
 * \internal
 * Generic support for ZXing 1D barcodes.
 */
template<ZXing::BarcodeFormat Format>
class ZXingOneDBarcode : public AbstractBarcodePrivate
{
public:
    explicit inline ZXingOneDBarcode()
        : AbstractBarcodePrivate(Barcode::OneDimension)
    {
    }

protected:
    inline QImage paintImage() override
    {
        try {
#if KZXING_VERSION < KZXING_VERSION_CHECK(3, 0, 0)
            ZXing::MultiFormatWriter writer(Format);
            const auto matrix = writer.encode(ZXingUtil::toStdWString(m_data), 1, 1);
            return ZXingUtil::toImage(matrix, m_foreground, m_background);
#else
            const auto barcode = ZXingUtil::createBarcode(m_data, Format);
            return ZXingUtil::toImage(ZXing::WriteBarcodeToImage(barcode), m_foreground, m_background);
#endif
        } catch (const std::invalid_argument &e) {
        }; // input too large or incompatible
        return {};
    }
};

}

#endif // PRISON_PDF417BARCODE_H
