# SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-prison-scanner.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-prison-scanner.h)

add_library(KF5PrisonScanner)
add_library(KF5::PrisonScanner ALIAS KF5PrisonScanner)

set_target_properties(KF5PrisonScanner PROPERTIES
    VERSION     ${PRISON_VERSION}
    SOVERSION   ${PRISON_SOVERSION}
    EXPORT_NAME PrisonScanner
)

target_sources(KF5PrisonScanner PRIVATE
    format.cpp
    scanresult.cpp
    videoscanner.cpp
    videoscannerframe.cpp
    videoscannerworker.cpp
)
ecm_generate_export_header(KF5PrisonScanner
    BASE_NAME PrisonScanner
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
)
target_include_directories(KF5PrisonScanner INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/PrisonScanner/>")
target_link_libraries(KF5PrisonScanner
    PUBLIC
        Qt${QT_MAJOR_VERSION}::Multimedia
    PRIVATE
        Qt${QT_MAJOR_VERSION}::Core
        ZXing::ZXing
)

install(TARGETS KF5PrisonScanner EXPORT KF5PrisonTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(PrisonScanner_CamelCase_HEADERS
    HEADER_NAMES
        Format
        ScanResult
        VideoScanner
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Prison
    REQUIRED_HEADERS PrisonScanner_HEADERS
)

install(
    FILES
        ${PrisonScanner_CamelCase_HEADERS}
        ${PrisonScanner_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/prisonscanner_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/PrisonScanner/Prison
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF5PrisonScanner_QCH
        NAME PrisonScanner
        BASE_NAME KF5PrisonScanner
        VERSION ${KF_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${PrisonScanner_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Multimedia_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PRISONSCANNER_EXPORT
            PRISONSCANNER_DEPRECATED
            PRISONSCANNER_DEPRECATED_EXPORT
            "PRISONSCANNER_DEPRECATED_VERSION(x, y, t)"
            "PRISONSCANNER_DEPRECATED_VERSION_BELATED(x, y, xt, yt, t)"
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
