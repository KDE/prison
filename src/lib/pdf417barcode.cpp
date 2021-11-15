/*
    SPDX-FileCopyrightText: 2021 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "pdf417barcode.h"

#include <ZXing/BitMatrix.h>
#include <ZXing/MultiFormatWriter.h>

#include <stdexcept>

using namespace Prison;

Pdf417Barcode::Pdf417Barcode()
    : AbstractBarcode(TwoDimensions)
{
}

QImage Pdf417Barcode::paintImage(const QSizeF &size)
{
    Q_UNUSED(size);

    std::wstring input;
    if (!data().isEmpty()) {
        input = data().toStdWString();
    } else {
        const auto b = byteArrayData();
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
                image.setPixel(x, y, matrix.get(x, y) ? foregroundColor().rgb() : backgroundColor().rgb());
            }
        }

        return image;
    } catch (const std::invalid_argument &e) {
    }; // input too large
    return {};
}
