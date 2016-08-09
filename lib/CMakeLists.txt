include(CMakePackageConfigHelpers)

include_directories(${QRENCODE_INCLUDE_DIR} ${DMTX_INCLUDE_DIR})
SET(prison_SRCS
    abstractbarcode.cpp
    code39barcode.cpp
    code93barcode.cpp
    datamatrixbarcode.cpp
    qrcodebarcode.cpp
    prison.cpp
)

add_library(KF5Prison ${prison_SRCS})

generate_export_header(KF5Prison BASE_NAME Prison)

add_library(KF5::Prison ALIAS KF5Prison)

target_include_directories(KF5Prison INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/prison/>")

target_link_libraries(KF5Prison
PUBLIC
   Qt5::Gui
PRIVATE
   ${DMTX_LIBRARIES} 
   ${QRENCODE_LIBRARIES} 
)

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
    Code39barcode
    Code93barcode
    Datamatrixbarcode
    Qrcodebarcode
    REQUIRED_HEADERS Prison_HEADERS
)

install(FILES ${Prison_CamelCase_HEADERS} DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/prison COMPONENT Devel)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/prison_export.h
    ${Prison_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/prison
    COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME Prison LIB_NAME KF5Prison DEPS "Qt5::Gui" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/prison)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

