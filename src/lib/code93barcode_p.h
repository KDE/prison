/*
    SPDX-FileCopyrightText: 2011 Geoffry Song <goffrie@gmail.com>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_CODE93BARCODE_H
#define PRISON_CODE93BARCODE_H

#include "abstractbarcode.h"

namespace Prison
{
/**
 * Code 93 Barcode generator
 */
class Code93Barcode : public Prison::AbstractBarcode
{
public:
    /**
     * creates a Code 93 generator
     */
    Code93Barcode();
    ~Code93Barcode() override;
    /**
     * This function generates the barcode
     * @return QImage containing a barcode, trying to approximate the requested sizes
     * @param size The requested size of the barcode, approximate. if the barcode generator can't generate it, it can return a null QImage
     */
    QImage paintImage(const QSizeF &size) override;
};
} // namespace

#endif // PRISON_CODE39BARCODE_H
