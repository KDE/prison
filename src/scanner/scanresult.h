/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_SCANRESULT_H
#define PRISON_SCANRESULT_H

#include "format.h"
#include "prisonscanner_export.h"

#include <QExplicitlySharedDataPointer>
#include <QMetaType>
#include <QRect>
#include <QVariant>

namespace Prison
{

class ScanResultPrivate;

/*!
 * \qmlvaluetype scanResult
 * \inqmlmodule org.kde.prison.scanner
 * \nativetype Prison::ScanResult
 *
 * \brief Result of a barcode scan attempt.
 *
 * A scan result consists of the barcode content (which can be text or
 * binary data), the barcode format and the position in the video frame
 * the barcode was detected.
 */

/*!
 * \class Prison::ScanResult
 * \inheaderfile Prison/ScanResult
 * \inmodule PrisonScanner
 *
 * \brief Result of a barcode scan attempt.
 *
 * A scan result consists of the barcode content (which can be text or
 * binary data), the barcode format and the position in the video frame
 * the barcode was detected.
 *
 * \since 5.94
 */
class PRISONSCANNER_EXPORT ScanResult
{
    Q_GADGET

    /*!
     * \qmlproperty bool scanResult::hasContent
     */

    /*!
     * \property Prison::ScanResult::hasContent
     */
    Q_PROPERTY(bool hasContent READ hasContent)

    /*!
     * \qmlproperty variant scanResult::content
     */

    /*!
     * \property Prison::ScanResult::content
     */
    Q_PROPERTY(QVariant content READ content)

    /*!
     * \qmlproperty bool scanResult::hasText
     */

    /*!
     * \property Prison::ScanResult::hasText
     */
    Q_PROPERTY(bool hasText READ hasText)

    /*!
     * \qmlproperty string scanResult::text
     */

    /*!
     * \property Prison::ScanResult::text
     */
    Q_PROPERTY(QString text READ text)

    /*!
     * \qmlproperty bool scanResult::hasBinaryData
     */

    /*!
     * \property Prison::ScanResult::hasBinaryData
     */
    Q_PROPERTY(bool hasBinaryData READ hasBinaryData)

    /*!
     * \qmlproperty bool scanResult::binaryData
     */

    /*!
     * \property Prison::ScanResult::binaryData
     */
    Q_PROPERTY(QByteArray binaryData READ binaryData)

    /*!
     * \qmlproperty enumeration scanResult::format
     * \qmlenumeratorsfrom Prison::Format::BarcodeFormat
     */

    /*!
     * \property Prison::ScanResult::format
     */
    Q_PROPERTY(Prison::Format::BarcodeFormat format READ format)

    /*!
     * \qmlproperty rect scanResult::boundingRect
     */

    /*!
     * \property Prison::ScanResult::boundingRect
     */
    Q_PROPERTY(QRect boundingRect READ boundingRect)

public:
    /*!
     */
    explicit ScanResult();
    ScanResult(const ScanResult &);
    ~ScanResult();
    ScanResult &operator=(const ScanResult &);

    /*!
     */
    bool operator==(const ScanResult &other) const;

    /*! Returns \c true if a barcode has been found. */
    bool hasContent() const;
    /*! The barcode content, either a QString or a QByteArray. */
    QVariant content() const;

    /*! Returns \c true if the found barcode contained a textual payload. */
    bool hasText() const;
    /*!
     * Returns the textual barcode content, if the content was text rather than binary data,
     * otherwise returns an empty string.
     */
    QString text() const;

    /*! Returns \c true if the found barcode contained a binary data payload. */
    bool hasBinaryData() const;
    /*!
     * Returns the binary data content, if the content was binary data rather than text,
     * otherwise returns an empty QByteArray.
     */
    QByteArray binaryData() const;

    /*! The format of the detected barcode. */
    Format::BarcodeFormat format() const;

    /*!
     * The bounding rectangle of the detected barcode in source coordinates.
     *
     * \note When using this to display an overlay in a view finder, this needs
     *  to be mapped to item coordinates.
     */
    QRect boundingRect() const;

private:
    friend class ScanResultPrivate;
    QExplicitlySharedDataPointer<ScanResultPrivate> d;
};

}

#endif // PRISON_SCANRESULT_H
