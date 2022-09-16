include(CMakePackageConfigHelpers)
if(TARGET Dmtx::Dmtx)
    set(HAVE_DMTX 1)
endif()
if (TARGET ZXing::ZXing)
    set(HAVE_ZXING 1)
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-prison.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-prison.h)

add_library(KF5Prison)
add_library(KF5::Prison ALIAS KF5Prison)

set_target_properties(KF5Prison PROPERTIES
    VERSION     ${PRISON_VERSION}
    SOVERSION   ${PRISON_SOVERSION}
    EXPORT_NAME Prison
)

target_sources(KF5Prison PRIVATE
    abstractbarcode.cpp
    abstractbarcode.h
    aztecbarcode.cpp
    aztecbarcode.h
    barcodeutil.cpp
    barcodeutil.h
    bitvector.cpp
    bitvector_p.h
    code128barcode.cpp
    code128barcode.h
    code39barcode.cpp
    code39barcode.h
    code93barcode.cpp
    code93barcode.h
    prison.cpp
    prison.h
    qrcodebarcode.cpp
    qrcodebarcode.h
    reedsolomon.cpp
    reedsolomon_p.h
)
if(TARGET Dmtx::Dmtx)
    target_sources(KF5Prison PRIVATE datamatrixbarcode.cpp datamatrixbarcode.h)
endif()
if(TARGET ZXing::ZXing)
    target_sources(KF5Prison PRIVATE pdf417barcode.cpp pdf417barcode.h)
endif()
kde_source_files_enable_exceptions(pdf417barcode.cpp)

ecm_qt_declare_logging_category(KF5Prison
    HEADER prison_debug.h
    IDENTIFIER Prison::Log
    CATEGORY_NAME kf.prison
    OLD_CATEGORY_NAMES kf5.prison
    DESCRIPTION "Prison (lib)"
    EXPORT PRISON
)

ecm_generate_export_header(KF5Prison
    BASE_NAME Prison
    GROUP_BASE_NAME KF
    VERSION ${KF_VERSION}
    DEPRECATED_BASE_VERSION 0
    DEPRECATION_VERSIONS 5.69 5.72
    EXCLUDE_DEPRECATED_BEFORE_AND_AT ${EXCLUDE_DEPRECATED_BEFORE_AND_AT}
)

target_include_directories(KF5Prison INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/Prison>")

target_link_libraries(KF5Prison
PUBLIC
   Qt${QT_MAJOR_VERSION}::Gui
PRIVATE
   QRencode::QRencode
)
if(TARGET Dmtx::Dmtx)
    target_link_libraries(KF5Prison PRIVATE Dmtx::Dmtx)
endif()
if(TARGET ZXing::ZXing)
    target_link_libraries(KF5Prison PRIVATE ZXing::ZXing)
endif()

install(TARGETS KF5Prison EXPORT KF5PrisonTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(Prison_CamelCase_HEADERS
    HEADER_NAMES
    AbstractBarcode
    Prison
    REQUIRED_HEADERS Prison_HEADERS
    OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/Prison
)

set(_all_headers
    ${Prison_HEADERS}
    ${Prison_CamelCase_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/prison_export.h
)

# So that the headers are found at build time
target_include_directories(KF5Prison PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>")

# To keep backwards compatibility with KF5, all headers are copied to <includedir>/KF5/Prison/prison,
# for KF6 everything goes into <includedir>/KF6/Prison/Prison only
if (QT_MAJOR_VERSION STREQUAL "5")
    install(
        FILES ${_all_headers}
        DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Prison/prison
        COMPONENT Devel
    )
endif()

install(
    FILES ${_all_headers}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Prison/Prison
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF5Prison_QCH
        NAME Prison
        BASE_NAME KF5Prison
        VERSION ${KF_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${Prison_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Gui_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            PRISON_EXPORT
            PRISON_DEPRECATED
            PRISON_DEPRECATED_EXPORT
            "PRISON_DEPRECATED_VERSION(x, y, t)"
            "PRISON_DEPRECATED_VERSION_BELATED(x, y, xt, yt, t)"
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

# INCLUDE_INSTALL_DIR has to be without prison/ subdir
# as the generated CamelCase headers have the prison/ path in the forward include
ecm_generate_pri_file(BASE_NAME Prison LIB_NAME KF5Prison DEPS "gui" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/Prison)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

