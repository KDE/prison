# SPDX-FileCopyrightText: 2022 Volker Krause <vkrause@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-prison-scanner.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-prison-scanner.h)

add_library(KF6PrisonScanner)
add_library(KF6::PrisonScanner ALIAS KF6PrisonScanner)

qt_extract_metatypes(KF6PrisonScanner)

set_target_properties(KF6PrisonScanner PROPERTIES
    VERSION     ${PRISON_VERSION}
    SOVERSION   ${PRISON_SOVERSION}
    EXPORT_NAME PrisonScanner
)

target_sources(KF6PrisonScanner PRIVATE
    format.cpp
    imagescanner.cpp
    scanresult.cpp
    videoscanner.cpp
    videoscannerframe.cpp
    videoscannerworker.cpp
)

kde_source_files_enable_exceptions(videoscannerworker.cpp imagescanner.cpp scanresult.cpp)

ecm_generate_export_header(KF6PrisonScanner
    BASE_NAME PrisonScanner
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    USE_VERSION_HEADER
    VERSION_BASE_NAME Prison
    DEPRECATED_BASE_VERSION 0
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

ecm_generate_qdoc(KF6PrisonScanner prisonscanner.qdocconf)

target_include_directories(KF6PrisonScanner
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/PrisonScanner>"
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/Prison>" # module version header
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>" # module version header
)
target_link_libraries(KF6PrisonScanner
    PUBLIC
        Qt6::Multimedia
    PRIVATE
        Qt6::Core
        ZXing::ZXing
)

install(TARGETS KF6PrisonScanner EXPORT KF6PrisonTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(PrisonScanner_CamelCase_HEADERS
    HEADER_NAMES
        Format
        ImageScanner
        ScanResult
        VideoScanner
    SHARED_PREFIX Prison
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
