include(CMakePackageConfigHelpers)
if(TARGET Dmtx::Dmtx)
    set(HAVE_DMTX 1)
endif()
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config-prison.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-prison.h)

set(prison_SRCS
    abstractbarcode.cpp
    aztecbarcode.cpp
    bitvector.cpp
    code39barcode.cpp
    code93barcode.cpp
    qrcodebarcode.cpp
    prison.cpp
    reedsolomon.cpp
)
if(TARGET Dmtx::Dmtx)
    list(APPEND prison_SRCS datamatrixbarcode.cpp)
endif()

ecm_qt_declare_logging_category(prison_SRCS HEADER prison_debug.h IDENTIFIER Prison::Log CATEGORY_NAME kf5.prison)
add_library(KF5Prison ${prison_SRCS})

generate_export_header(KF5Prison BASE_NAME Prison)

add_library(KF5::Prison ALIAS KF5Prison)

target_include_directories(KF5Prison INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/prison/>")
target_include_directories(KF5Prison PUBLIC "$<BUILD_INTERFACE:${prison_SOURCE_DIR}>")

target_link_libraries(KF5Prison
PUBLIC
   Qt5::Gui
PRIVATE
   QRencode::QRencode
)
if(TARGET Dmtx::Dmtx)
    target_link_libraries(KF5Prison PRIVATE Dmtx::Dmtx)
endif()

set_target_properties(KF5Prison PROPERTIES
    VERSION ${PRISON_VERSION_STRING}
    SOVERSION ${PRISON_SOVERSION}
    EXPORT_NAME Prison
)

install(TARGETS KF5Prison EXPORT KF5PrisonTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(Prison_CamelCase_HEADERS
    HEADER_NAMES
    AbstractBarcode
    Prison
    PREFIX PRISON
    REQUIRED_HEADERS Prison_HEADERS
)

install(FILES
    ${Prison_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/prison COMPONENT Devel)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/prison_export.h
    ${Prison_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/prison
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF5Prison_QCH
        NAME Prison
        BASE_NAME KF5Prison
        VERSION ${KF5_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
            ${Prison_HEADERS}
        MD_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md"
        LINK_QCHS
            Qt5Gui_QCH
        BLANK_MACROS
            PRISON_EXPORT
            PRISON_DEPRECATED
            PRISON_DEPRECATED_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

ecm_generate_pri_file(BASE_NAME Prison LIB_NAME KF5Prison DEPS "Qt5::Gui" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/prison)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

