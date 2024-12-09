/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include <Prison/Format>
#include <Prison/ScanResult>
#include <Prison/VideoScanner>

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

struct VideoScannerForeign {
    Q_GADGET
    QML_NAMED_ELEMENT(VideoScanner)
    QML_FOREIGN(Prison::VideoScanner)
};

namespace FormatForeign
{
Q_NAMESPACE
QML_NAMED_ELEMENT(Format)
QML_FOREIGN_NAMESPACE(Prison::Format)
};

struct ScanResultForeign {
    Q_GADGET
    QML_VALUE_TYPE(scanResult)
    QML_FOREIGN(Prison::ScanResult)
};
