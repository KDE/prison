/*
    SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#include "barcodequickitem.h"

#include <prison/prison.h>

#include <QQmlExtensionPlugin>

class PrisonQuickPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.kde.prison")

public:
    PrisonQuickPlugin(QObject *parent = nullptr)
        : QQmlExtensionPlugin(parent)
    {
    }

    void registerTypes(const char *uri) override;
};

void PrisonQuickPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Prison::BarcodeQuickItem>(uri, 1, 0, "Barcode");
}

#include "prisonquickplugin.moc"
