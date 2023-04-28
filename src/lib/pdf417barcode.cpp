/*
    SPDX-FileCopyrightText: 2021 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "pdf417barcode_p.h"

#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>

#include <stdexcept>

using namespace Prison;

Pdf417Barcode::Pdf417Barcode()
    : AbstractBarcodePrivate(AbstractBarcode::TwoDimensions)
{
}

QImage Pdf417Barcode::paintImage()
{
    std::wstring input;
    const bool isBinary = q->data().isEmpty();
    if (!isBinary) {
        input = q->data().toStdWString();
    } else {
        const auto b = q->byteArrayData();
        input.reserve(b.size());
        // ensure we explicitly copy unsigned bytes here, ie. each byte ends up in the least significant byte of
        // the std::wstring. If we end up converting to a signed value inbetween, values > 127 end up negative and
        // will be wrongly represented in the std::wstring
        for (uint8_t c : b) {
            input.push_back(c);
        }
    }

    try {
        ZXing::MultiFormatWriter writer(ZXing::BarcodeFormat::PDF417);
        // ISO/IEC 15438:2006(E) §5.8.3 Quiet Zone
        writer.setMargin(2);
        if (isBinary) {
            writer.setEncoding(ZXing::CharacterSet::BINARY);
        }
        // aspect ratio 4 is hard-coded in ZXing
        const auto matrix = writer.encode(input, 4, 1);

        QImage image(matrix.width(), matrix.height(), QImage::Format_ARGB32);
        for (int y = 0; y < matrix.height(); ++y) {
            for (int x = 0; x < matrix.width(); ++x) {
                image.setPixel(x, y, matrix.get(x, y) ? m_foreground.rgb() : m_background.rgb());
            }
        }

        return image;
    } catch (const std::invalid_argument &e) {
    }; // input too large
    return {};
}

QSizeF Pdf417Barcode::preferredSize(qreal devicePixelRatio) const
{
    return m_cache.size() * (devicePixelRatio < 2 ? 2 : 1);
}
