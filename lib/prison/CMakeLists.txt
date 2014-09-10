include(CMakePackageConfigHelpers)

set(PRISON_VERSION_MAJOR "1")
set(PRISON_VERSION_MINOR "2")
set(PRISON_VERSION_PATCH "0")



set(PRISON_VERSION "${PRISON_VERSION_MAJOR}.${PRISON_VERSION_MINOR}.${PRISON_VERSION_PATCH}")
set(PRISON_VERSION_STRING "${PRISON_VERSION}")


include_directories(${QRENCODE_INCLUDE_DIR} ${DMTX_INCLUDE_DIR})
SET(    prison_SRCS
        abstractbarcode.cpp
        code39barcode.cpp
        code93barcode.cpp
        datamatrixbarcode.cpp
        qrcodebarcode.cpp
        )

add_library(KF5Prison ${prison_SRCS})

generate_export_header(KF5Prison BASE_NAME prison)

add_library(KF5::Prison ALIAS KF5Prison)

target_include_directories(KF5Prison INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/PRISON/prison>")
target_include_directories(KF5Prison PUBLIC "$<BUILD_INTERFACE:${Prison_SOURCE_DIR}/lib/prison;${Prison_BINARY_DIR}/lib/prison>")


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
  Code39Barcode
  Code93Barcode
  DataMatrixBarcode
  QRCodeBarcode
  PREFIX PRISON
  REQUIRED_HEADERS Prison_HEADERS
)

install(FILES ${Prison_CamelCase_HEADERS} DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/PRISON/prison COMPONENT Devel)


configure_file(
   PrisonConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PrisonConfig.cmake @ONLY
)


install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/prison_export.h
    ${Prison_HEADERS}
    DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/PRISON/prison
    COMPONENT Devel
)

ecm_generate_pri_file(BASE_NAME Prison LIB_NAME KF5Prison DEPS "Qt5::Gui" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KF5_INCLUDE_INSTALL_DIR}/PRISON)
install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

