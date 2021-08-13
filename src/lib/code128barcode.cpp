/*
    SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "code128barcode.h"
#include "bitvector_p.h"
#include "prison_debug.h"

#include <QImage>
#include <QPainter>

using namespace Prison;

enum {
    SymbolSize = 11,
    StopPatternSize = 13,
    StopPattern = 108,
    QuietZone = 10,
};

enum CodeSet : uint8_t {
    CodeSetA = 0,
    CodeSetB = 1,
    CodeSetC = 2,
    CodeSetUnknown = 3,
};

enum CodeSetOp : uint8_t {
    None = 255,
    StartA = 103,
    StartB = 104,
    StartC = 105,
    Shift = 98,
    LatchA = 101,
    LatchB = 100,
    LatchC = 99,
};

Code128Barcode::Code128Barcode()
    : AbstractBarcode(AbstractBarcode::OneDimension)
{
}
Code128Barcode::~Code128Barcode() = default;

QImage Code128Barcode::paintImage(const QSizeF &size)
{
    Q_UNUSED(size);

    const auto bits = encode(data().isEmpty() ? byteArrayData() : data().toLatin1());
    const auto width = bits.size() + 2 * QuietZone;

    QImage img(width, 1, QImage::Format_ARGB32);
    img.fill(backgroundColor());
    QPainter p(&img);
    for (int i = 0; i < bits.size(); ++i) {
        if (bits.at(i)) {
            img.setPixel(QuietZone + i, 0, foregroundColor().rgb());
        }
    }

    return img;
}

// Code 128 symbol table
// ### this is the perfect use-case for binary literals (as the binary pattern
// corresponds to the line pattern), adjust this once KF5 moves to C++14
static const uint16_t code128_symbols[] = {
    1740, // 0b11011001100 // 0
    1644, // 0b11001101100
    1638, // 0b11001100110
    1176, // 0b10010011000
    1164, // 0b10010001100
    1100, // 0b10001001100
    1224, // 0b10011001000
    1220, // 0b10011000100
    1124, // 0b10001100100
    1608, // 0b11001001000
    1604, // 0b11001000100 // 10
    1572, // 0b11000100100
    1436, // 0b10110011100
    1244, // 0b10011011100
    1230, // 0b10011001110
    1484, // 0b10111001100
    1260, // 0b10011101100
    1254, // 0b10011100110
    1650, // 0b11001110010
    1628, // 0b11001011100
    1614, // 0b11001001110 // 20
    1764, // 0b11011100100
    1652, // 0b11001110100
    1902, // 0b11101101110
    1868, // 0b11101001100
    1836, // 0b11100101100
    1830, // 0b11100100110
    1892, // 0b11101100100
    1844, // 0b11100110100
    1842, // 0b11100110010
    1752, // 0b11011011000 // 30
    1734, // 0b11011000110
    1590, // 0b11000110110
    1304, // 0b10100011000
    1112, // 0b10001011000
    1094, // 0b10001000110
    1416, // 0b10110001000
    1128, // 0b10001101000
    1122, // 0b10001100010
    1672, // 0b11010001000
    1576, // 0b11000101000 // 40
    1570, // 0b11000100010
    1464, // 0b10110111000
    1422, // 0b10110001110
    1134, // 0b10001101110
    1496, // 0b10111011000
    1478, // 0b10111000110
    1142, // 0b10001110110
    1910, // 0b11101110110
    1678, // 0b11010001110
    1582, // 0b11000101110 // 50
    1768, // 0b11011101000
    1762, // 0b11011100010
    1774, // 0b11011101110
    1880, // 0b11101011000
    1862, // 0b11101000110
    1814, // 0b11100010110
    1896, // 0b11101101000
    1890, // 0b11101100010
    1818, // 0b11100011010
    1914, // 0b11101111010 // 60
    1602, // 0b11001000010
    1930, // 0b11110001010
    1328, // 0b10100110000
    1292, // 0b10100001100
    1200, // 0b10010110000
    1158, // 0b10010000110
    1068, // 0b10000101100
    1062, // 0b10000100110
    1424, // 0b10110010000
    1412, // 0b10110000100 // 70
    1232, // 0b10011010000
    1218, // 0b10011000010
    1076, // 0b10000110100
    1074, // 0b10000110010
    1554, // 0b11000010010
    1616, // 0b11001010000
    1978, // 0b11110111010
    1556, // 0b11000010100
    1146, // 0b10001111010
    1340, // 0b10100111100 // 80
    1212, // 0b10010111100
    1182, // 0b10010011110
    1508, // 0b10111100100
    1268, // 0b10011110100
    1266, // 0b10011110010
    1956, // 0b11110100100
    1940, // 0b11110010100
    1938, // 0b11110010010
    1758, // 0b11011011110
    1782, // 0b11011110110 // 90
    1974, // 0b11110110110
    1400, // 0b10101111000
    1310, // 0b10100011110
    1118, // 0b10001011110
    1512, // 0b10111101000
    1506, // 0b10111100010
    1960, // 0b11110101000
    1954, // 0b11110100010
    1502, // 0b10111011110
    1518, // 0b10111101110 // 100
    1886, // 0b11101011110
    1966, // 0b11110101110
    1668, // 0b11010000100
    1680, // 0b11010010000
    1692, // 0b11010011100
    1594, // 0b11000111010
    1720, // 0b11010111000
    6379 // 0b1100011101011
};

static uint8_t symbolForCharacter(const QByteArray &data, int index, CodeSet set)
{
    const auto c1 = data.at(index);
    switch (set) {
    case CodeSetA:
        return (c1 < ' ') ? c1 + 64 : c1 - ' ';
    case CodeSetB:
        return c1 - ' ';
    case CodeSetC: {
        const auto c2 = data.at(index + 1);
        return ((c1 - '0') * 10) + c2 - '0';
    }
    case CodeSetUnknown:
        Q_UNREACHABLE();
    }

    Q_UNREACHABLE();
    return {};
}

struct CodeSetChange {
    CodeSet set;
    CodeSetOp symbol;
};

static bool isInCodeSetA(char c)
{
    return c <= 95;
}

static bool isInCodeSetB(char c)
{
    // ### this does not consider FNC4 high byte encoding
    return c >= 32;
}

static CodeSetChange opForData(const QByteArray &data, int index, CodeSet currentSet)
{
    // determine if Code C makes sense at this point
    int codeC = 0;
    for (int i = index; i < data.size(); ++i, ++codeC) {
        if (data.at(i) < '0' || data.at(i) > '9') {
            break;
        }
    }
    if (currentSet == CodeSetC && codeC >= 2) { // already in C
        return {CodeSetC, None};
    }
    if (codeC >= 6 // that's always good enough
        || (index == 0 && codeC >= 4) // beginning of data
        || (index + codeC == data.size() && codeC >= 4) // end of data
        || (codeC == data.size() && codeC == 2) // 2 ...
        || (codeC == data.size() && codeC == 4)) // ... or 4 as the entire data
    {
        return currentSet == CodeSetUnknown ? CodeSetChange{CodeSetC, StartC} : CodeSetChange{CodeSetC, LatchC};
    }

    // if we are in Code A or Code B, check if we need to switch for the next char
    // this is a shortcut to prevent the below more extensive search from making this O(n²) in the common case
    if ((currentSet == CodeSetA && isInCodeSetA(data.at(index))) || (currentSet == CodeSetB && isInCodeSetB(data.at(index)))) {
        return {currentSet, None};
    }

    // we need to switch to A or B, select which one, and select whether to use start, shift or latch
    const auto nextA = isInCodeSetA(data.at(index));
    const auto nextB = isInCodeSetB(data.at(index));

    // count how many following characters we could encode in A or B
    int countA = 0;
    for (int i = index + 1; i < data.size(); ++i, ++countA) {
        if (!isInCodeSetA(data.at(i))) {
            break;
        }
    }
    int countB = 0;
    for (int i = index + 1; i < data.size(); ++i, ++countB) {
        if (!isInCodeSetB(data.at(i))) {
            break;
        }
    }

    // select how we want to switch to Code A or Code B, biased to B as that's the more useful one in general
    switch (currentSet) {
    case CodeSetUnknown:
        // if we are at the start, take whichever code will get us further, or the only one that works
        if (nextA && nextB) {
            return countA > countB ? CodeSetChange{CodeSetA, StartA} : CodeSetChange{CodeSetB, StartB};
        }
        return nextA ? CodeSetChange{CodeSetA, StartA} : CodeSetChange{CodeSetB, StartB};
    case CodeSetC:
        // same for Code C
        if (nextA && nextB) {
            return countA > countB ? CodeSetChange{CodeSetA, LatchA} : CodeSetChange{CodeSetB, LatchB};
        }
        return nextA ? CodeSetChange{CodeSetA, LatchA} : CodeSetChange{CodeSetB, LatchB};
    case CodeSetA:
        // switch or latch to B?
        return CodeSetChange{CodeSetB, countB >= countA ? LatchB : Shift};
    case CodeSetB:
        // switch or latch to A?
        return CodeSetChange{CodeSetA, countA > countB ? LatchA : Shift};
    }

    Q_UNREACHABLE();
    return CodeSetChange{currentSet, None};
}

BitVector Code128Barcode::encode(const QByteArray &data) const
{
    BitVector v;
    if (data.isEmpty()) {
        return v;
    }

    // determine code set for start
    const auto op = opForData(data, 0, CodeSetUnknown);
    auto currentSet = op.set;

    // write start code
    qCDebug(Log) << "start symbol:" << op.symbol << code128_symbols[op.symbol];
    v.appendMSB(code128_symbols[op.symbol], SymbolSize);

    uint32_t checksum = op.symbol;
    uint32_t checksumWeight = 1;

    for (int i = 0; i < data.size(); i += currentSet == CodeSetC ? 2 : 1) {
        if (static_cast<uint8_t>(data.at(i)) > 127) { // FNC4 encoding not implemented yet
            continue;
        }

        // perform code switch if needed
        const auto op = opForData(data, i, currentSet);
        if (op.symbol != None) {
            qCDebug(Log) << "op symbol:" << op.symbol << code128_symbols[op.symbol];
            v.appendMSB(code128_symbols[op.symbol], SymbolSize);
            checksum += op.symbol * checksumWeight++;
        }

        // encode current symbol
        const auto symbol = symbolForCharacter(data, i, op.set);
        qCDebug(Log) << "data symbol:" << symbol << code128_symbols[symbol];
        v.appendMSB(code128_symbols[symbol], SymbolSize);
        checksum += symbol * checksumWeight++;

        // update current code set
        if (op.symbol != Shift) {
            currentSet = op.set;
        }
    }

    // encode checksum
    qCDebug(Log) << "checksum:" << checksum << code128_symbols[checksum % 103];
    v.appendMSB(code128_symbols[checksum % 103], SymbolSize);

    // add stop pattern
    v.appendMSB(code128_symbols[StopPattern], StopPatternSize);
    return v;
}
