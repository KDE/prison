/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include <Prison/Format>
#include <Prison/VideoScanner>

#include <QQmlEngine>
#include <QQmlExtensionPlugin>

class PrisonScannerQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.prison.scanner")

public:
    PrisonScannerQuickPlugin(QObject *parent = nullptr)
        : QQmlExtensionPlugin(parent)
    {
    }

    void registerTypes(const char *uri) override;
};

void PrisonScannerQuickPlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableMetaObject(Prison::Format::staticMetaObject, uri, 1, 0, "Format", {});
    qmlRegisterType<Prison::VideoScanner>(uri, 1, 0, "VideoScanner");
}

#include "prisonscannerquickplugin.moc"
