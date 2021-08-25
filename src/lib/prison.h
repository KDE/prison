/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_PRISON_H
#define PRISON_PRISON_H
#include "abstractbarcode.h"
#include "prison_export.h"

/**
 * @namespace Prison
 *
 * Provides classes and methods for generating barcodes.
 */
namespace Prison
{
class AbstractBarcode;
/**
 * possible supported barcode types
 */
enum BarcodeType {
    /** Null barcode */
    Null = 0,
    /** QRCode 2d barcode */
    QRCode = 1,
    /** DataMatrix 2d barcode */
    DataMatrix = 2,
    /** Aztec 2d barcode */
    Aztec,
    /** Code39 barcode */
    Code39,
    /** Code93 barcode */
    Code93,
    /** Code 128 barcode */
    Code128,
    /** PDF417 barcode */
    PDF417,
};
/**
 * Factory method to create a barcode of a given type.
 * @param type barcode type. See @ref BarcodeType enum for values
 * @return a barcode provider, or a null pointer if unsupported. Ownership is passed to the caller.
 */
PRISON_EXPORT Prison::AbstractBarcode *createBarcode(BarcodeType type);
}

#endif // PRISON_PRISON_H
