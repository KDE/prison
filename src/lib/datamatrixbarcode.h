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

#ifndef PRISON_DATAMATRIXBARCODE_H
#define PRISON_DATAMATRIXBARCODE_H

#include "abstractbarcode.h"
#include "prison_export.h"

namespace Prison {
/**
 * This is a Datamatrix barcode generator that uses libdmtx
 * for the actual generation of barcodes.
 */
class DataMatrixBarcode : public Prison::AbstractBarcode {
    public:
        /**
        * creates a datamatrixbarcode generator
        */
        DataMatrixBarcode();
        ~DataMatrixBarcode() override;
    protected:
        /**
        * This is the function doing the actual work in generating the barcode
        * @return QImage containing a DataMatrix, trying to approximate the requested sizes
        */
        QImage paintImage(const QSizeF& size) override;
    private:
        class Private;
        Private *d;
};
}

#endif // PRISON_DATAMATRIXBARCODE_H
