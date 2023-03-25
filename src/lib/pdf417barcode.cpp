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
    if (!q->data().isEmpty()) {
        input = q->data().toStdWString();
    } else {
        const auto b = q->byteArrayData();
        input.reserve(b.size());
        std::copy(b.begin(), b.end(), std::back_inserter(input));
    }

    try {
        ZXing::MultiFormatWriter writer(ZXing::BarcodeFormat::PDF417);
        // ISO/IEC 15438:2006(E) §5.8.3 Quiet Zone
        writer.setMargin(2);
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
