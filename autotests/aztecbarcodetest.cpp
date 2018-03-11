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

#include "../src/lib/aztecbarcode.h"
#include "../src/lib/bitvector_p.h"

#include <QImage>
#include <QObject>
#include <qtest.h>

Q_DECLARE_METATYPE(Prison::BitVector)

using namespace Prison;

class AztecBarcodeTest : public QObject
{
Q_OBJECT
private Q_SLOTS:
    void testAztecEncode_data()
    {
        QTest::addColumn<QByteArray>("input");
        QTest::addColumn<BitVector>("output");

        QTest::newRow("empty") << QByteArray() << BitVector();
        BitVector v;
        v.appendMSB(12, 5); v.appendMSB(5, 5); v.appendMSB(6, 5);
        QTest::newRow("all uppper") << QByteArray("KDE") << v;
        v.clear();
        v.appendMSB(28, 5); v.appendMSB(12, 5); v.appendMSB(5, 5); v.appendMSB(6, 5);
        QTest::newRow("all lower") << QByteArray("kde") << v;
        v.clear();
        v.appendMSB(12, 5); v.appendMSB(28, 5); v.appendMSB(5, 5); v.appendMSB(6, 5);
        QTest::newRow("upper -> lower latch") << QByteArray("Kde") << v;
        v.clear();
        v.appendMSB(28, 5); v.appendMSB(2, 5); v.appendMSB(29, 5); v.appendMSB(30, 5); v.appendMSB(16, 5); v.appendMSB(16, 5);
        QTest::newRow("lower -> punct latch") << QByteArray("a++") << v;
        v.clear();
        v.appendMSB(30, 5); v.appendMSB(6, 4); v.appendMSB(4, 4);
        QTest::newRow("digit") << QByteArray("42") << v;
        v.clear();
        v.appendMSB(29, 5); v.appendMSB(30, 5); v.appendMSB(25, 5); v.appendMSB(24, 5); v.appendMSB(31, 5); v.appendMSB(30, 5); v.appendMSB(11, 4); v.appendMSB(2, 4);
        QTest::newRow("punct -> digit latch") << QByteArray(">=90") << v;
        v.clear();
        v.appendMSB(30, 5); v.appendMSB(10, 4); v.appendMSB(3, 4); v.appendMSB(14, 4); v.appendMSB(29, 5); v.appendMSB(30, 5); v.appendMSB(13, 5); v.appendMSB(14, 5);
        QTest::newRow("digit -> punct latch") << QByteArray("81()") << v;
        v.clear();
        v.appendMSB(29, 5); v.appendMSB(11, 5); v.appendMSB(8, 5);
        QTest::newRow("mixed") << QByteArray("\n\a") << v;
        v.clear();
        v.appendMSB(29, 5); v.appendMSB(30, 5); v.appendMSB(2, 5); v.appendMSB(2, 5);
        QTest::newRow("CR LF") << QByteArray("\r\n\r\n") << v;
        v.clear();
        v.appendMSB(31, 5); v.appendMSB(2, 5); v.appendMSB(128, 8); v.appendMSB(129, 8);
        QTest::newRow("binary") << QByteArray("\x80\x81") << v;
        v.clear();
        v.appendMSB(31, 5); v.appendMSB(2, 5); v.appendMSB(255, 8); v.appendMSB(254, 8); v.appendMSB(28, 5); v.appendMSB(3, 5);
        QTest::newRow("binary/lower") << QByteArray("\xff\xfe" "b") << v;
        v.clear();
        v.appendMSB(12, 5); v.appendMSB(0, 5); v.appendMSB(6, 5);
        QTest::newRow("upper -> punct shift") << QByteArray("K!") << v;
        v.clear();
        v.appendMSB(30, 5); v.appendMSB(9, 4); v.appendMSB(4, 4); v.appendMSB(15, 4); v.appendMSB(6, 5); v.appendMSB(5, 4);
        QTest::newRow("digit -> upper shift") << QByteArray("72E3") << v;
        v.clear();
        v.appendMSB(25, 5); v.appendMSB(1, 5); v.appendMSB(26, 5);
        QTest::newRow("upper space") << QByteArray("X Y") << v;
        v.clear();
        v.appendMSB(20, 5); v.appendMSB(0, 5); v.appendMSB(4, 5); v.appendMSB(23, 5);
        QTest::newRow("upper punct double char shift") << QByteArray("S, V") << v;
        v.clear();
        v.appendMSB(17, 5); v.appendMSB(0, 5); v.appendMSB(17, 5); v.appendMSB(18, 5);
        QTest::newRow("upper ambigious punct shift") << QByteArray("P,Q") << v;
        v.clear();
        v.appendMSB(30, 5); v.appendMSB(13, 4); v.appendMSB(7, 4);
        QTest::newRow("digit ambigious punct latch") << QByteArray(".5") << v;
    }

    void testAztecEncode()
    {
        QFETCH(QByteArray, input);
        QFETCH(BitVector, output);

        AztecBarcode code;
        const auto v = code.aztecEncode(input);
        if (v != output) {
            qDebug() << "Actual  :" << v;
            qDebug() << "Expected:" << output;
        }
        QCOMPARE(v, output);
    }

    void testStuffAndPad_data()
    {
        QTest::addColumn<BitVector>("input");
        QTest::addColumn<BitVector>("output");
        QTest::addColumn<int>("codeWordSize");

        BitVector in, out;
        QTest::newRow("emtpy") << in << out << 4;
        in.appendMSB(0x3, 2); out.appendMSB(0xf, 4);
        QTest::newRow("pad only") << in << out << 4;
        in.clear(); out.clear();
        in.appendMSB(0xe0, 8); out.appendMSB(0xe13, 12);
        QTest::newRow("stuff and pad") << in << out << 4;
        in.clear(); out.clear();
        in.appendMSB(0, 6); out.appendMSB(0x11, 8);
        QTest::newRow("stuff only") << in << out << 4;
    }

    void testStuffAndPad()
    {
        QFETCH(BitVector, input);
        QFETCH(BitVector, output);
        QFETCH(int, codeWordSize);
        AztecBarcode code;
        const auto res= code.bitStuffAndPad(input, codeWordSize);
        QCOMPARE(res.size(), output.size());
        if (res != output) {
            qDebug() << "Actual  :" << res;
            qDebug() << "Expected:" << output;
        }
        QCOMPARE(res, output);
    }

    void testFullGrid()
    {
        AztecBarcode code;
        QImage img(151, 151, QImage::Format_ARGB32_Premultiplied);
        img.fill(code.backgroundColor());
        code.paintFullGrid(&img);

        QImage ref(QStringLiteral(":/rendering/aztec-full-grid.png"));
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }

    void testCompactGrid()
    {
        AztecBarcode code;
        QImage img(27, 27, QImage::Format_ARGB32_Premultiplied);
        img.fill(code.backgroundColor());
        code.paintCompactGrid(&img);
        img.save(QStringLiteral("aztec-compact-grid.png"));

        QImage ref(QStringLiteral(":/rendering/aztec-compact-grid.png"));
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }

    void testFullData_data()
    {
        QTest::addColumn<BitVector>("data");
        QTest::addColumn<QString>("refName");
        QTest::addColumn<int>("layer");

        BitVector v;
        for (int i = 0; i < 1248; ++i)
            v.appendLSB(0x9249, 16);
        QTest::newRow("1001-31") << v << QStringLiteral("aztec-full-data-1001.png") << 32;

        v.clear();
        for (int i = 0; i < 1248 * 8; ++i)
            v.appendLSB(0x2, 2);
        QTest::newRow("0101-31") << v << QStringLiteral("aztec-full-data-0101.png") << 32;

        v.clear();
        for (int i = 0; i < 1248; ++i)
            v.appendLSB(0xffff, 16);
        QTest::newRow("1111-31") << v << QStringLiteral("aztec-full-data-1111.png") << 32;

        v.clear();
        for (int i = 0; i < 704 * 4; ++i)
            v.appendLSB(0x1, 2);
        QTest::newRow("1010-15") << v << QStringLiteral("aztec-full-data-1010.png") << 16;

        v.clear();
        for (int i = 0; i < 16; ++i)
            v.appendLSB(0xCC, 8);
        QTest::newRow("0011-0") << v << QStringLiteral("aztec-full-data-0011.png") << 1;
    }

    void testFullData()
    {
        QFETCH(BitVector, data);
        QFETCH(QString, refName);
        QFETCH(int, layer);

        AztecBarcode code;
        QImage img(151, 151, QImage::Format_ARGB32_Premultiplied);
        img.fill(code.backgroundColor());
        code.paintFullData(&img, data, layer);
        img.save(refName);

        QImage ref(QStringLiteral(":/rendering/") + refName);
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }

    void testFullModeMessage_data()
    {
        QTest::addColumn<BitVector>("data");
        QTest::addColumn<QString>("refName");

        BitVector v;
        for (int i = 0; i < 8; ++i)
            v.appendMSB(i + 1, 5);
        QTest::newRow("1234") << v << QStringLiteral("aztec-full-mode-1234.png");

        v.clear();
        for (int i = 0; i < 8; ++i)
            v.appendLSB(i + 1, 5);
        QTest::newRow("1234-rev") << v << QStringLiteral("aztec-full-mode-1234-rev.png");

        v.clear();
        for (int i = 0; i < 4; ++i)
            v.appendMSB(0xffff, 10);
        QTest::newRow("1111") << v << QStringLiteral("aztec-full-mode-1111.png");
    }

    void testFullModeMessage()
    {
        QFETCH(BitVector, data);
        QFETCH(QString, refName);

        AztecBarcode code;
        QImage img(151, 151, QImage::Format_ARGB32_Premultiplied);
        img.fill(code.backgroundColor());
        code.paintFullModeMessage(&img, data);
        img.save(refName);

        QImage ref(QStringLiteral(":/rendering/") + refName);
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }

    void testCompactData_data()
    {
        QTest::addColumn<BitVector>("data");
        QTest::addColumn<QString>("refName");
        QTest::addColumn<int>("layer");

        BitVector v;
        for (int i = 0; i < 304; ++i)
            v.appendLSB(0x9249, 16);
        QTest::newRow("1001-3") << v << QStringLiteral("aztec-compact-data-1001.png") << 4;

        v.clear();
        for (int i = 0; i < 608 * 4; ++i)
            v.appendLSB(0x2, 2);
        QTest::newRow("0101-3") << v << QStringLiteral("aztec-compact-data-0101.png") << 4;

        v.clear();
        for (int i = 0; i < 304; ++i)
            v.appendLSB(0xffff, 16);
        QTest::newRow("1111-3") << v << QStringLiteral("aztec-compact-data-1111.png") << 4;

        v.clear();
        for (int i = 0; i < 102 * 4; ++i)
            v.appendLSB(0x1, 2);
        QTest::newRow("1010-2") << v << QStringLiteral("aztec-compact-data-1010.png") << 3;

        v.clear();
        for (int i = 0; i < 13; ++i)
            v.appendLSB(0xCC, 8);
        QTest::newRow("0011-0") << v << QStringLiteral("aztec-compact-data-0011.png") << 1;
    }

    void testCompactData()
    {
        QFETCH(BitVector, data);
        QFETCH(QString, refName);
        QFETCH(int, layer);

        AztecBarcode code;
        QImage img(27, 27, QImage::Format_ARGB32_Premultiplied);
        img.fill(code.backgroundColor());
        code.paintCompactData(&img, data, layer);
        img.save(refName);

        QImage ref(QStringLiteral(":/rendering/") + refName);
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }

    void testCompactModeMessage_data()
    {
        QTest::addColumn<BitVector>("data");
        QTest::addColumn<QString>("refName");

        BitVector v;
        for (int i = 0; i < 4; ++i)
            v.appendMSB(i + 1, 7);
        QTest::newRow("1234") << v << QStringLiteral("aztec-compact-mode-1234.png");

        v.clear();
        for (int i = 0; i < 4; ++i)
            v.appendLSB(i + 1, 7);
        QTest::newRow("1234-rev") << v << QStringLiteral("aztec-compact-mode-1234-rev.png");

        v.clear();
        for (int i = 0; i < 4; ++i)
            v.appendMSB(0xffff, 7);
        QTest::newRow("1111") << v << QStringLiteral("aztec-compact-mode-1111.png");
    }

    void testCompactModeMessage()
    {
        QFETCH(BitVector, data);
        QFETCH(QString, refName);

        AztecBarcode code;
        QImage img(151, 151, QImage::Format_ARGB32_Premultiplied);
        img.fill(code.backgroundColor());
        code.paintCompactModeMessage(&img, data);
        img.save(refName);

        QImage ref(QStringLiteral(":/rendering/") + refName);
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }

    void testCodeGen_data()
    {
        QTest::addColumn<QString>("input");
        QTest::addColumn<QString>("refName");

        QTest::newRow("short compact") << QStringLiteral("KF5::Prison") << "aztec-complete-compact1.png";
        QTest::newRow("compact 3 layer") << QStringLiteral("M1KRAUSE/VOLKER       ABCDEFG TXLRIXBT 0212 309Y014E0063 100") << "aztec-complete-compact3.png";
        QTest::newRow("long compact") << QStringLiteral("KF5::Prison - the barcode generation library of KDE Frameworks 5!") << "aztec-complete-compact4.png";
        QTest::newRow("short full") << QStringLiteral("KF5::Prison - the MIT licensed free software barcode generation library of KDE Frameworks 5!") << "aztec-complete-full5.png";
        QTest::newRow("long full") << QString::fromLatin1(
            "Permission is hereby granted, free of charge, to any person\n"
            "obtaining a copy of this software and associated documentation\n"
            "files (the \"Software\"), to deal in the Software without\n"
            "restriction, including without limitation the rights to use,\n"
            "copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
            "copies of the Software, and to permit persons to whom the\n"
            "Software is furnished to do so, subject to the following\n"
            "conditions:\n\n"
            "The above copyright notice and this permission notice shall be\n"
            "included in all copies or substantial portions of the Software.\n\n"
            "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND,\n"
            "EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES\n"
            "OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND\n"
            "NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT\n"
            "HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,\n"
            "WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING\n"
            "FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR\n"
            "OTHER DEALINGS IN THE SOFTWARE.") << "aztec-complete-big.png";
    }

    void testCodeGen()
    {
        QFETCH(QString, input);
        QFETCH(QString, refName);

        AztecBarcode code;
        code.setData(input);
        const auto img = code.paintImage({200, 200});
        img.save(refName);

        QImage ref(QStringLiteral(":/encoding/") + refName);
        ref = ref.convertToFormat(img.format());
        QCOMPARE(img, ref);
    }
};

QTEST_APPLESS_MAIN(AztecBarcodeTest)

#include "aztecbarcodetest.moc"
