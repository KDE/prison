include_directories(${QRENCODE_INCLUDE_DIR} ${DMTX_INCLUDE_DIR})
SET(    prison_SRC
        abstractbarcode.cpp
        barcodewidget.cpp
        barcodeitem.cpp
        datamatrixbarcode.cpp
        qrcodebarcode.cpp
        )

add_library(prison SHARED ${prison_SRC})
target_link_libraries(prison ${DMTX_LIBRARIES} ${QRENCODE_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

set_target_properties(prison PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_PRISON)

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

install( TARGETS prison DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         abstractbarcode.h
         AbstractBarcode
         barcodeitem.h
         BarcodeItem
         barcodewidget.h
         BarcodeWidget
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
set(LIBPATH ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX})

configure_file(
   PrisonConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/PrisonConfig.cmake @ONLY
)

install( FILES
         ${CMAKE_CURRENT_BINARY_DIR}/PrisonConfig.cmake
	 DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/cmake/Prison
)


