/*
    SPDX-FileCopyrightText: 2010-2014 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_QRCODEBARCODE_H
#define PRISON_QRCODEBARCODE_H

#include "abstractbarcode.h"

namespace Prison
{
/**
 * QRCode Barcode generator ; uses libqrencode to do the actual encoding
 * of the barcode.
 */
class QRCodeBarcode : public Prison::AbstractBarcode
{
public:
    /**
     * creates a QRCode generator
     */
    QRCodeBarcode();
    ~QRCodeBarcode() override;
    /**
     * This is the function doing the actual work in generating the barcode
     * @return QImage containing a QRCode, trying to approximate the requested sizes
     * @param size The requested size of the barcode, approximate. if the barcode generator can't get the data to fit in there, it might be a null QImage
     */
    QImage paintImage(const QSizeF &size) override;
};
} // namespace

#endif // PRISON_QRCODEBARCODE_H
