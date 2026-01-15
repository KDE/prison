/*
    SPDX-FileCopyrightText: 2021 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_ZXINGUTILS_P_H
#define PRISON_ZXINGUTILS_P_H

#include <string>

namespace ZXing
{
class Barcode;
class BitMatrix;
class CreatorOptions;
class Image;
}

class QColor;
class QImage;
class QVariant;

namespace Prison
{
namespace ZXingUtil
{
/*!
 * \internal
 *
 * Convert barcode content (string or byte array) to the input
 *  format expected by ZXing.
 */
std::wstring toStdWString(const QVariant &data);

/*!
 * \internal
 *
 * Create a barcode from the given data, using binary or text format as appropriate.
 */
ZXing::Barcode createBarcode(const QVariant &data, const ZXing::CreatorOptions &options);

/*!
 * \internal
 *
 * Convert the bitmatrix output of ZXing to a QImage.
 */
QImage toImage(const ZXing::BitMatrix &matrix, const QColor &foreground, const QColor &background);
QImage toImage(const ZXing::Image &img, const QColor &foreground, const QColor &background);
}

}

#endif
