# SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

ecm_add_qml_module(prisonscannerquickplugin URI "org.kde.prison.scanner" VERSION 1.0 CLASSNAME "PrisonScannerQuickPlugin")
target_sources(prisonscannerquickplugin PRIVATE prisonscannerquickplugin.cpp)
target_link_libraries(prisonscannerquickplugin PRIVATE Qt${QT_MAJOR_VERSION}::Quick KF5::PrisonScanner)
ecm_finalize_qml_module(prisonscannerquickplugin DESTINATION ${KDE_INSTALL_QMLDIR})
