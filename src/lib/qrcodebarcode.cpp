/*
    SPDX-FileCopyrightText: 2010-2016 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "qrcodebarcode.h"
#include <QColor>
#include <qrencode.h>

using namespace Prison;

QRCodeBarcode::QRCodeBarcode()
    : AbstractBarcode(AbstractBarcode::TwoDimensions)
{
}
QRCodeBarcode::~QRCodeBarcode() = default;

QImage QRCodeBarcode::paintImage(const QSizeF &size)
{
    Q_UNUSED(size);
    const QByteArray trimmedData(data().trimmed().toUtf8());
    QRcode *code = QRcode_encodeString8bit(trimmedData.constData(), 0, QR_ECLEVEL_Q);
    if (!code) {
        return QImage();
    }
    const int margin = 2;
    /*32 bit colors, 8 bit pr byte*/
    uchar *img = new uchar[4 * sizeof(char *) * (2 * margin + code->width) * (2 * margin * +code->width)];
    uchar *p = img;
    QByteArray background;
    background.resize(4);
    background[3] = qAlpha(backgroundColor().rgba());
    background[2] = qRed(backgroundColor().rgba());
    background[1] = qGreen(backgroundColor().rgba());
    background[0] = qBlue(backgroundColor().rgba());
    QByteArray foreground;
    foreground.resize(4);
    foreground[3] = qAlpha(foregroundColor().rgba());
    foreground[2] = qRed(foregroundColor().rgba());
    foreground[1] = qGreen(foregroundColor().rgba());
    foreground[0] = qBlue(foregroundColor().rgba());
    for (int row = 0; row < code->width + 2 * margin; row++) {
        for (int col = 0; col < code->width + 2 * margin; col++) {
            if (row < margin || row >= (code->width + margin) || col < margin || col >= (code->width + margin)) {
                /*4 bytes for color*/
                for (int i = 0; i < 4; i++) {
                    *p = background[i];
                    p++;
                }
            } else {
                int c = (row - margin) * code->width + (col - margin);
                /*it is bit 1 that is the interesting bit for us from libqrencode*/
                if (code->data[c] & 1) {
                    /*4 bytes for color*/
                    for (int i = 0; i < 4; i++) {
                        *p = foreground[i];
                        p++;
                    }
                } else {
                    /*4 bytes for color*/
                    for (int i = 0; i < 4; i++) {
                        *p = background[i];
                        p++;
                    }
                }
            }
        }
    }

    const auto result =
        QImage(img, code->width + 2 * margin, code->width + 2 * margin, QImage::Format_ARGB32).copy(); // deep copy as we are going to delete img
    delete[] img;
    QRcode_free(code);
    return result;
}
