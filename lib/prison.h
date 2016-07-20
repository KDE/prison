/*
    Copyright (c) 2010-2016 Sune Vuorela <sune@vuorela.dk>

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

#ifndef PRISON_PRISON_H
#define PRISON_PRISON_H
#include "prison_export.h"
#include "abstractbarcode.h"

namespace Prison {
    class AbstractBarcode;
    /**
     * possible supported barcode types
     */
    enum BarcodeType
    {
        /** Null barcode */
        Null = 0,
        /** QRCode 2d barcode */
        QRCode = 1,
        /** DataMatrix 2d barcode */
        DataMatrix = 2,
        /** Aztec 2d barcode (currently unsupported)*/
        Aztec,
        /** Code39 barcode */
        Code39,
        /** Code93 barcode */
        Code93

    };
    /**
     * Factory method to create a barcode of a given type.
     * @param type barcode type. See @ref BarcodeType enum for values
     * @return a barcode provider, or a null pointer if unsupported. Ownership is passed to the caller.
     */
    PRISON_EXPORT Prison::AbstractBarcode* createBarcode(BarcodeType type);
}

#endif // PRISON_PRISON_H
