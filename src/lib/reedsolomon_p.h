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

#ifndef PRISON_REEDSOLOMON_P_H
#define PRISON_REEDSOLOMON_P_H

#include <memory>

namespace Prison {

class BitVector;

/** Reed Solomon checksum generator. */
class ReedSolomon
{
public:
    enum GF {
        GF16 = 0x13,
        GF64 = 0x43,
        GF256 = 0x12d,
        GF1024 = 0x409,
        GF4096 = 0x1069
    };

    /** Initialize a Reed Solomon encoder with the Galois Field
     *  described by the bit pattern of @p polynom, for generating
     *  @p symbolCount error correction symbols.
     */
    explicit ReedSolomon(int polynom, int symbolCount);
    ReedSolomon(const ReedSolomon&) = delete;
    ~ReedSolomon();

    /** Encode the content of @p input and return the resulting
     *  code words.
     */
    BitVector encode(const BitVector &input) const;

private:
    std::unique_ptr<int[]> m_logTable;
    std::unique_ptr<int[]> m_antiLogTable;
    std::unique_ptr<int[]> m_polynom;
    int m_symCount = 0;
    int m_symSize = 0;
};

}

#endif // PRISON_REEDSOLOMON_P_H
