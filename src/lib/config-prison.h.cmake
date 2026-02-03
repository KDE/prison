/*
    SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

    SPDX-License-Identifier: MIT
*/

#ifndef PRISON_CONFIG_H
#define PRISON_CONFIG_H

#cmakedefine01 HAVE_DMTX
#cmakedefine01 HAVE_ZXING

#if HAVE_ZXING

// ensure to not clash with the ZXING_* macros of zxing itself!
#define KZXING_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))

#define KZXING_VERSION_MAJOR @ZXing_VERSION_MAJOR@
#define KZXING_VERSION_MINOR @ZXing_VERSION_MINOR@
#define KZXING_VERSION_PATCH @ZXing_VERSION_PATCH@

#define KZXING_VERSION KZXING_VERSION_CHECK(KZXING_VERSION_MAJOR, KZXING_VERSION_MINOR, KZXING_VERSION_PATCH)

#endif

#endif
