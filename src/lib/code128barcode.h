/*
    Copyright (c) 2018 Volker Krause <vkrause@kde.org>

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

#ifndef PRISON_CODE128BARCODE_H
#define PRISON_CODE128BARCODE_H

#include "abstractbarcode.h"

class Code128BarcodeTest;

namespace Prison {

class BitVector;

/** Code 128 barcode
 *  @see https://en.wikipedia.org/wiki/Code_128
 */
class Code128Barcode : public AbstractBarcode
{
public:
    Code128Barcode();
    ~Code128Barcode() override;

protected:
    QImage paintImage(const QSizeF& size) override;

private:
    friend class ::Code128BarcodeTest;
    BitVector encode(const QByteArray &data) const;
};

}

#endif // PRISON_CODE128BARCODE_H
