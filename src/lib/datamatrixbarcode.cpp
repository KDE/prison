/*
    SPDX-FileCopyrightText: 2010-2014 Sune Vuorela <sune@vuorela.dk>

    SPDX-License-Identifier: MIT
*/

#include "datamatrixbarcode.h"
#include <dmtx.h>
using namespace Prison;

DataMatrixBarcode::DataMatrixBarcode()
    : AbstractBarcode(AbstractBarcode::TwoDimensions)
{
}
DataMatrixBarcode::~DataMatrixBarcode() = default;

QImage DataMatrixBarcode::paintImage(const QSizeF &size)
{
    Q_UNUSED(size);
    if (data().size() > 1200) {
        return QImage();
    }

    DmtxEncode *enc = dmtxEncodeCreate();
    dmtxEncodeSetProp(enc, DmtxPropPixelPacking, DmtxPack32bppRGBX);
    dmtxEncodeSetProp(enc, DmtxPropModuleSize, 1);
    dmtxEncodeSetProp(enc, DmtxPropMarginSize, 2);

    QByteArray trimmedData(data().trimmed().toUtf8());
    DmtxPassFail result = dmtxEncodeDataMatrix(enc, trimmedData.length(), reinterpret_cast<unsigned char *>(trimmedData.data()));
    if (result == DmtxFail) {
        dmtxEncodeDestroy(&enc);
        return QImage();
    }
    Q_ASSERT(enc->image->width == enc->image->height);

    QImage ret;

    if (foregroundColor() == Qt::black && backgroundColor() == Qt::white) {
        QImage tmp(enc->image->pxl, enc->image->width, enc->image->height, QImage::Format_ARGB32);
        // we need to copy, because QImage generated from a char pointer requires the
        // char pointer to be kept around forever, and manually deleted.
        ret = tmp.copy();
    } else {
        if (enc->image->width > 0) {
            int size = enc->image->width * enc->image->height * 4;
            uchar *img = new uchar[size];
            QByteArray background(4, '\0');
            background[3] = qAlpha(backgroundColor().rgba());
            background[2] = qRed(backgroundColor().rgba());
            background[1] = qGreen(backgroundColor().rgba());
            background[0] = qBlue(backgroundColor().rgba());
            QByteArray foreground(4, '\0');
            foreground[3] = qAlpha(foregroundColor().rgba());
            foreground[2] = qRed(foregroundColor().rgba());
            foreground[1] = qGreen(foregroundColor().rgba());
            foreground[0] = qBlue(foregroundColor().rgba());
            for (int i = 1; i < size; i += 4) {
                QByteArray color;
                if (enc->image->pxl[i] == 0x00) {
                    color = foreground;
                } else {
                    color = background;
                }
                for (int j = 0; j < 4; j++) {
                    img[i - 1 + j] = color[j];
                }
            }
            QImage tmp(img, enc->image->width, enc->image->height, QImage::Format_ARGB32);
            // we need to copy, because QImage generated from a char pointer requires the
            // char pointer to be kept around forever, and manually deleted.
            ret = tmp.copy();
            delete[] img;
        }
    }
    dmtxEncodeDestroy(&enc);
    return ret;
}
