/*
    SPDX-FileCopyrightText: 2021 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "config-prison.h"

#include "pdf417barcode_p.h"
#include "zxingutil_p.h"

#if KZXING_VERSION < KZXING_VERSION_CHECK(3, 0, 0)
#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>
#else
#include <ZXing/Barcode.h>
#include <ZXing/CreateBarcode.h>
#include <ZXing/WriteBarcode.h>
#endif

#include <stdexcept>

using namespace Prison;

Pdf417Barcode::Pdf417Barcode()
    : AbstractBarcodePrivate(Barcode::TwoDimensions)
{
}

QImage Pdf417Barcode::paintImage()
{
    try {
#if KZXING_VERSION < KZXING_VERSION_CHECK(3, 0, 0)
        ZXing::MultiFormatWriter writer(ZXing::BarcodeFormat::PDF417);
        // ISO/IEC 15438:2006(E) §5.8.3 Quiet Zone
        writer.setMargin(2);
        if (m_data.userType() == QMetaType::QByteArray) {
            writer.setEncoding(ZXing::CharacterSet::BINARY);
        }
        // aspect ratio 4 is hard-coded in ZXing
        const auto matrix = writer.encode(ZXingUtil::toStdWString(m_data), 4, 1);
        return ZXingUtil::toImage(matrix, m_foreground, m_background);
#else
        const auto barcode = ZXingUtil::createBarcode(m_data, ZXing::BarcodeFormat::PDF417);
        // ISO/IEC 15438:2006(E) §5.8.3 Quiet Zone
        const auto writeOpts = ZXing::WriterOptions().addQuietZones(2);
        return ZXingUtil::toImage(ZXing::WriteBarcodeToImage(barcode, writeOpts), m_foreground, m_background);
#endif
    } catch (const std::invalid_argument &e) {
    }; // input too large
    return {};
}

QSizeF Pdf417Barcode::preferredSize(qreal devicePixelRatio) const
{
    return m_cache.size() * (devicePixelRatio < 2 ? 2 : 1);
}
