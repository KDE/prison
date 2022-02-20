/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_SCANRESULT_P_H
#define PRISON_SCANRESULT_P_H

#include "scanresult.h"

#include <QSharedData>

namespace Prison
{

class ScanResultPrivate : public QSharedData
{
public:
    static inline ScanResultPrivate *get(const ScanResult &q)
    {
        return q.d.data();
    }

    QVariant content;
    QRect boundingRect;
    Format::BarcodeFormat format = Format::NoFormat;
};

}
#endif // PRISON_SCANRESULT_P_H
