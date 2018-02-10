/*
    Copyright (c) 2018 Volker Krause <vkrause@kde.org>

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

import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import org.kde.prison 1.0 as Prison
Rectangle {
    width: 640
    height: 320
    color: "lightsteelblue"
    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: contentEdit
                Layout.fillWidth: true
                text: "KF5::Prison - The KDE barcode generation framework."
            }
            ComboBox {
                id: typeCombobox
                model: [ "Null", "QRCode", "DataMatrix", "Aztec", "Code39", "Code93" ]
                currentIndex: 3
            }
        }

        Prison.Barcode {
            Layout.fillWidth: true
            Layout.fillHeight: true
            content: contentEdit.text
            barcodeType: typeCombobox.currentIndex
//             foregroundColor: "red"
//             backgroundColor: "green"
        }
    }
}
