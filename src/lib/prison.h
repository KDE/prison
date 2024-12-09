/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_PRISON_H
#define PRISON_PRISON_H

#include "prison_export.h"

/*!
 * \namespace Prison
 * \inheaderfile Prison/Prison
 * \inmodule Prison
 *
 * \brief Provides classes and methods for generating barcodes.
 */
namespace Prison
{
/*!
 * possible supported barcode types
 *
 * \value QRCode QRCode 2d barcode
 * \value DataMatrix DataMatrix 2d barcode
 * \value Aztec Aztec 2d barcode
 * \value Code39 Code39 barcode
 * \value Code93 Code93 barcode
 * \value Code128 Code 128 barcode
 * \value PDF417 PDF417 barcode
 * \value EAN13 EAN13 barcode
 */
enum BarcodeType {
    QRCode,
    DataMatrix,
    Aztec,
    Code39,
    Code93,
    Code128,
    PDF417,
    EAN13,
};
}

#endif // PRISON_PRISON_H
