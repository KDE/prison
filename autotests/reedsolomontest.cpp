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

#include "../src/lib/bitvector_p.h"
#include "../src/lib/reedsolomon_p.h"

#include <QDebug>
#include <QObject>
#include <qtest.h>

Q_DECLARE_METATYPE(Prison::BitVector)

using namespace Prison;

class ReedSolomonTest : public QObject
{
Q_OBJECT
private Q_SLOTS:
    void rsTest_data()
    {
        QTest::addColumn<int>("poly");
        QTest::addColumn<int>("symCount");
        QTest::addColumn<BitVector>("input");
        QTest::addColumn<BitVector>("output");

        BitVector in, out;
        out.appendMSB(0, 20);
        QTest::newRow("empty") << (int)ReedSolomon::GF16 << 5 << in << out;

        in.clear(); out.clear();
        in.appendMSB(0x5c, 8);
        out.appendMSB(7, 6); out.appendMSB(5, 7); out.appendMSB(0x4d, 7);
        QTest::newRow("GF16") << (int)ReedSolomon::GF16 << 5 << in << out;
    }

    void rsTest()
    {
        QFETCH(int, poly);
        QFETCH(int, symCount);
        QFETCH(BitVector, input);
        QFETCH(BitVector, output);

        ReedSolomon rs(poly, symCount);
        const auto res = rs.encode(input);
        QCOMPARE(res.size(), output.size());
        if (res != output) {
            qDebug() << "Actual  :" << res;
            qDebug() << "Expected:" << output;
        }
        QCOMPARE(res, output);
    }
};

QTEST_APPLESS_MAIN(ReedSolomonTest)

#include "reedsolomontest.moc"
