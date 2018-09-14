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

#include "../src/lib/code128barcode.h"
#include "../src/lib/bitvector_p.h"

#include <QImage>
#include <QObject>
#include <qtest.h>

Q_DECLARE_METATYPE(Prison::BitVector)

using namespace Prison;

class Code128BarcodeTest : public QObject
{
Q_OBJECT
private Q_SLOTS:
    void testEncode_data()
    {
        QTest::addColumn<QByteArray>("input");
        QTest::addColumn<BitVector>("output");

        BitVector v;
        QTest::newRow("empty") << QByteArray() << v;
        v.appendMSB(1680, 11); v.appendMSB(1554, 11); v.appendMSB(1062, 11); v.appendMSB(1424, 11); v.appendMSB(1220, 11); v.appendMSB(6379, 13);
        QTest::newRow("all lower") << QByteArray("kde") << v;
        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1422, 11); v.appendMSB(1416, 11); v.appendMSB(1128, 11); v.appendMSB(1764, 11); v.appendMSB(6379, 13);
        QTest::newRow("all uppper") << QByteArray("KDE") << v;

        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1614, 11); v.appendMSB(1764, 11); v.appendMSB(6379, 13);
        QTest::newRow("1 digit") << QByteArray("4") << v;
        v.clear();
        v.appendMSB(1692, 11); v.appendMSB(1464, 11); v.appendMSB(1134, 11); v.appendMSB(6379, 13);
        QTest::newRow("2 digits") << QByteArray("42") << v;
        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1614, 11); v.appendMSB(1650, 11); v.appendMSB(1650, 11); v.appendMSB(1124, 11); v.appendMSB(6379, 13);
        QTest::newRow("3 digits") << QByteArray("422") << v;
        v.clear();
        v.appendMSB(1692, 11); v.appendMSB(1464, 11); v.appendMSB(1902, 11); v.appendMSB(1782, 11); v.appendMSB(6379, 13);
        QTest::newRow("4 digits") << QByteArray("4223") << v;

        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1814, 11); v.appendMSB(1260, 11); v.appendMSB(1260, 11); v.appendMSB(1896, 11); v.appendMSB(1814, 11); v.appendMSB(6379, 13);
        QTest::newRow("mixed") << QByteArray("X00Y") << v;

        v.clear();
        v.appendMSB(1668, 11); v.appendMSB(1292, 11); v.appendMSB(1292, 11); v.appendMSB(6379, 13);
        QTest::newRow("null") << QByteArray("\0", 1) << v;
        v.clear();
        v.appendMSB(1668, 11); v.appendMSB(1422, 11); v.appendMSB(1416, 11); v.appendMSB(1128, 11); v.appendMSB(1292, 11); v.appendMSB(1412, 11); v.appendMSB(6379, 13);
        QTest::newRow("Code A only") << QByteArray("KDE\0", 4) << v;

        v.clear();
        v.appendMSB(1668, 11); v.appendMSB(1292, 11); v.appendMSB(1518, 11); v.appendMSB(1554, 11); v.appendMSB(1062, 11); v.appendMSB(1424, 11); v.appendMSB(1616, 11); v.appendMSB(6379, 13);
        QTest::newRow("Start A -> Latch B") << QByteArray("\0kde", 4) << v;
        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1554, 11); v.appendMSB(1062, 11); v.appendMSB(1886, 11); v.appendMSB(1292, 11); v.appendMSB(1292, 11); v.appendMSB(1602, 11); v.appendMSB(6379, 13);
        QTest::newRow("Start B -> Latch A") << QByteArray("kd\0\0", 4) << v;

        v.clear();
        v.appendMSB(1668, 11); v.appendMSB(1292, 11); v.appendMSB(1954, 11); v.appendMSB(1118, 11); v.appendMSB(1590, 11); v.appendMSB(1292, 11); v.appendMSB(1328, 11); v.appendMSB(6379, 13);
        QTest::newRow("Start A -> Shift B") << QByteArray("\0~@\0", 4) << v;
        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1974, 11); v.appendMSB(1954, 11); v.appendMSB(1292, 11); v.appendMSB(1310, 11); v.appendMSB(1844, 11); v.appendMSB(6379, 13);
        QTest::newRow("Start B -> Shift A") << QByteArray("{\0}", 3) << v;

        v.clear();
        v.appendMSB(1692, 11); v.appendMSB(1436, 11); v.appendMSB(1112, 11); v.appendMSB(1518, 11); v.appendMSB(1304, 11); v.appendMSB(1112, 11); v.appendMSB(1158, 11); v.appendMSB(6379, 13);
        QTest::newRow("Start C -> Latch B") << QByteArray("1234AB") << v;
        v.clear();
        v.appendMSB(1680, 11); v.appendMSB(1304, 11); v.appendMSB(1112, 11); v.appendMSB(1502, 11); v.appendMSB(1436, 11); v.appendMSB(1112, 11); v.appendMSB(1966, 11); v.appendMSB(6379, 13);
        QTest::newRow("Start B -> Latch C") << QByteArray("AB1234") << v;
    }

    void testEncode()
    {
        QFETCH(QByteArray, input);
        QFETCH(BitVector, output);

        Code128Barcode code;
        const auto v = code.encode(input);
        if (v != output) {
            qDebug() << "Actual  :" << v;
            qDebug() << "Expected:" << output;
        }
        QCOMPARE(v, output);
    }
};

QTEST_APPLESS_MAIN(Code128BarcodeTest)

#include "code128barcodetest.moc"
