include(CMakePackageConfigHelpers)

if(QT5_BUILD)
   set(PRISON_VERSION_MAJOR "1")
else()
   set(PRISON_VERSION_MAJOR "0")
endif()
set(PRISON_VERSION_MINOR "2")
set(PRISON_VERSION_PATCH "0")



set(PRISON_VERSION "${PRISON_VERSION_MAJOR}.${PRISON_VERSION_MINOR}.${PRISON_VERSION_PATCH}")
set(PRISON_VERSION_STRING "${PRISON_VERSION}")


include_directories(${QRENCODE_INCLUDE_DIR} ${DMTX_INCLUDE_DIR})
SET(    prison_SRC
        abstractbarcode.cpp
        barcodewidget.cpp
        barcodeitem.cpp
        code39barcode.cpp
        code93barcode.cpp
        datamatrixbarcode.cpp
        qrcodebarcode.cpp
        )

add_library(prison SHARED ${prison_SRC})
target_link_libraries(prison ${DMTX_LIBRARIES} ${QRENCODE_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

set_target_properties(prison PROPERTIES VERSION "${PRISON_VERSION_STRING}" SOVERSION "${PRISON_VERSION_MAJOR}" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_PRISON)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

include(CheckCXXCompilerFlag)

if (CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)
    check_cxx_compiler_flag(-fvisibility=hidden _HAVE_GCC_VISIBILITY)
    if (_HAVE_GCC_VISIBILITY)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")

        check_cxx_compiler_flag(-fvisibility-inlines-hidden _HAVE_GCC_VISIBILITY_INLINES)
        if (_HAVE_GCC_VISIBILITY_INLINES)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")
        endif (_HAVE_GCC_VISIBILITY_INLINES)
    endif (_HAVE_GCC_VISIBILITY)
endif (CMAKE_COMPILER_IS_GNUCXX AND NOT WIN32)

if(QT5_BUILD)
  install(TARGETS prison ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})
else()
  install( TARGETS prison DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )
endif()

install( FILES
         abstractbarcode.h
         AbstractBarcode
         barcodeitem.h
         BarcodeItem
         barcodewidget.h
         BarcodeWidget
         code39barcode.h
         Code39Barcode
         code93barcode.h
         Code93Barcode
         datamatrixbarcode.h
         DataMatrixBarcode
         qrcodebarcode.h
         QRCodeBarcode
         prison_export.h
         DESTINATION ${CMAKE_INSTALL_PREFIX}/include/prison COMPONENT devel
         )

set(INCLUDE_DIRECTORY ${CMAKE_INSTALL_PREFIX}/include)
get_target_property(LIB_OUT_NAME prison LOCATION)
get_filename_component(LIB_OUT_NAME ${LIB_OUT_NAME} NAME)

if(QT5_BUILD)
  set(LIBPATH ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/Prison")
else()
  set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})
  set(CMAKECONFIG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/Prison")
endif()

configure_file(
   PrisonConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PrisonConfig.cmake @ONLY
)

# this file is used by to check if the installed version can be used.
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/PrisonConfigVersion.cmake
                                 VERSION "${PRISON_VERSION_STRING}"
                                 COMPATIBILITY SameMajorVersion
                                )


install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/PrisonConfig.cmake
         ${CMAKE_CURRENT_BINARY_DIR}/PrisonConfigVersion.cmake
	 DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)


