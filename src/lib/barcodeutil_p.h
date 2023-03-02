/*
    SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: MIT
*/

#ifndef BARCODEUTIL_H
#define BARCODEUTIL_H
#include <QList>
namespace Prison
{
namespace BarCodeUtil
{
QList<bool> barSequence(const char *str);
}
}

#endif // BARCODEUTIL_H
