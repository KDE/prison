/*
    SPDX-FileCopyrightText: 2021 Volker Krause <vkrause@kde.org>
    SPDX-FileCopyrightText: 2023 Kai Uwe Broulik <kde@broulik.de>
    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_MECARD_H
#define PRISON_MECARD_H

#include <QString>
#include <QStringList>
#include <QVariantMap>

#include "prison_export.h"

#include <memory>
#include <optional>

namespace Prison
{

/*!
 * \class Prison::MeCard
 * \inheaderfile Prison/MeCard
 * \inmodule Prison
 *
 * Parser for the MeCard format.
 * This was originally used for a more compact vCard representation, but today
 * is mostly relevant for Wifi configuration QR codes.
 * \sa https://en.wikipedia.org/wiki/MeCard_(QR_code)
 * \sa https://github.com/zxing/zxing/wiki/Barcode-Contents#wi-fi-network-config-android-ios-11
 * \since 5.101
 */
class PRISON_EXPORT MeCard
{
public:
    MeCard(MeCard &&other) noexcept;

    MeCard &operator=(MeCard &&other) noexcept;

    ~MeCard();

    /*!
     * Parse the given string
     *
     * \a data The string to parse
     *
     * Returns a MeCard, if parsing was successful, a nullopt otherwise.
     */
    static std::optional<MeCard> parse(const QString &data);

    /*!
     * Get the MeCard header.
     *
     * If you just want to identify the card,
     * use headerView() instead.
     */
    QString header() const;
    /*!
     * Get the MeCard header as a string view.
     *
     * Useful for identifying the type of card.
     */
    QStringView headerView() const;
    /*!
     * Get the value for a given key.
     *
     * Convenience method for getting the first value
     * if only one value is expected.
     */
    QString value(QStringView key) const;
    /*!
     * Get the list of values for a given key.
     */
    QStringList values(QStringView key) const;

    /*!
     * Get the parsed data as QVariantMap.
     */
    QVariantMap toVariantMap() const;

private:
    explicit MeCard();

    friend class MeCardPrivate;
    std::unique_ptr<class MeCardPrivate> d;
};

} // namespace Prison

#endif // PRISON_MECARD_H
