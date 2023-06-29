/*
    SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
    SPDX-License-Identifier: MIT
*/

#include "scanresult.h"
#include "scanresult_p.h"

using namespace Prison;

ScanResult::ScanResult()
    : d(new ScanResultPrivate)
{
}

ScanResult::ScanResult(const ScanResult &) = default;
ScanResult::~ScanResult() = default;
ScanResult &ScanResult::operator=(const ScanResult &) = default;

bool ScanResult::operator==(const ScanResult &other) const
{
    return d->content == other.d->content && d->boundingRect == other.d->boundingRect && d->format == other.d->format;
}

bool ScanResult::hasContent() const
{
    return !d->content.isNull();
}

QVariant ScanResult::content() const
{
    return d->content;
}

bool ScanResult::hasText() const
{
    return d->content.userType() == QMetaType::QString;
}

QString ScanResult::text() const
{
    return hasText() ? d->content.toString() : QString();
}

bool ScanResult::hasBinaryData() const
{
    return d->content.userType() == QMetaType::QByteArray;
}

QByteArray ScanResult::binaryData() const
{
    return hasBinaryData() ? d->content.toByteArray() : QByteArray();
}

Format::BarcodeFormat ScanResult::format() const
{
    return d->format;
}

QRect ScanResult::boundingRect() const
{
    return d->boundingRect;
}

#include "moc_scanresult.cpp"
