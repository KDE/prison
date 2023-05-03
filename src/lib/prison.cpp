/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "prison.h"
#include <config-prison.h>

#include "abstractbarcode_p.h"
#include "aztecbarcode_p.h"
#include "code128barcode_p.h"
#include "code39barcode_p.h"
#include "code93barcode_p.h"
#include "datamatrixbarcode_p.h"
#include "pdf417barcode_p.h"
#include "qrcodebarcode_p.h"
#if HAVE_ZXING
#include "zxingonedbarcode_p.h"
#endif

Prison::AbstractBarcode *Prison::createBarcode(BarcodeType type)
{
    switch (type) {
    case Prison::Null:
        return nullptr;
    case Prison::QRCode:
        return AbstractBarcodePrivate::makeBarcode(new QRCodeBarcode);
    case Prison::DataMatrix:
#if HAVE_DMTX
        return AbstractBarcodePrivate::makeBarcode(new DataMatrixBarcode);
#else
        return nullptr;
#endif
    case Prison::Aztec:
        return AbstractBarcodePrivate::makeBarcode(new AztecBarcode);
    case Prison::Code39:
        return AbstractBarcodePrivate::makeBarcode(new Code39Barcode);
    case Prison::Code93:
        return AbstractBarcodePrivate::makeBarcode(new Code93Barcode);
    case Prison::Code128:
        return AbstractBarcodePrivate::makeBarcode(new Code128Barcode);
#if HAVE_ZXING
    case Prison::PDF417:
        return AbstractBarcodePrivate::makeBarcode(new Pdf417Barcode);
    case Prison::EAN13:
        return AbstractBarcodePrivate::makeBarcode(new ZXingOneDBarcode<ZXing::BarcodeFormat::EAN13>);
#endif
    }
    return nullptr;
}
