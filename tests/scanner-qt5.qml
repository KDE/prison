/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15
import org.kde.prison.scanner 1.0 as Prison

ApplicationWindow {
    width: 1024
    height: 768
    visible: true

    VideoOutput {
        id: viewFinder
        anchors.fill: parent
        source: camera
        filters: [scanner]
    }

    Prison.VideoScanner {
        id: scanner
//         formats: Prison.Format.QRCode | Prison.Format.Aztec
        onResultChanged: {
            if (result.hasText) {
                console.log(result.text, result.format);
            } else if (result.hasBinaryData) {
                console.log("<binary content>", result.format);
            } else {
                console.log("no barcode found");
            }
        }
    }

    Camera {
        id: camera
    }

    Rectangle {
        color: "#80ff0000"
        x: viewFinder.mapRectToItem(scanner.result.boundingRect).x
        y: viewFinder.mapRectToItem(scanner.result.boundingRect).y
        width: viewFinder.mapRectToItem(scanner.result.boundingRect).width
        height: viewFinder.mapRectToItem(scanner.result.boundingRect).height
    }
}
