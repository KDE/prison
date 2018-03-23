/*
    Copyright (c) 2017 Volker Krause <vkrause@kde.org>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/

#ifndef PRISON_AZTECBARCODE_H
#define PRISON_AZTECBARCODE_H

#include "abstractbarcode.h"

class AztecBarcodeTest;

namespace Prison {

class BitVector;

/** Aztec code generator. */
class AztecBarcode : public AbstractBarcode
{
public:
    AztecBarcode();
    ~AztecBarcode() override;

protected:
    QImage paintImage(const QSizeF& size) override;

private:
    friend class ::AztecBarcodeTest;

    BitVector aztecEncode(const QByteArray &data) const;
    BitVector bitStuffAndPad(const BitVector &input, int codeWordSize) const;

    void paintFullGrid(QImage *img) const;
    void paintFullData(QImage *img, const BitVector &data, int layerCount) const;
    void paintFullModeMessage(QImage *img, const BitVector &modeData) const;
    QImage cropAndScaleFull(QImage *img, int layerCount, int size);

    void paintCompactGrid(QImage *img) const;
    void paintCompactData(QImage *img, const BitVector &data, int layerCount) const;
    void paintCompactModeMessage(QImage *img, const BitVector &modeData) const;
    QImage cropAndScaleCompact(QImage *img, int layerCount, int size);
};

}

#endif // PRISON_AZTECCODE_H
