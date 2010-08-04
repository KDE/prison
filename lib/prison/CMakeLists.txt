SET(prison_SRC 
        abstractbarcodewidget.cpp
        abstractbarcodeitem.cpp
        datamatriximage.cpp
        datamatrixwidget.cpp
        datamatrixitem.cpp
        datamatriximage.cpp
        qrcodeitem.cpp
        qrcodewidget.cpp
        qrcodeimage.cpp
        )

add_library(prison SHARED ${prison_SRC})
target_link_libraries(prison ${DMTX_LIBRARIES} ${QRENCODE_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

set_target_properties(prison PROPERTIES VERSION "0.0.0" SOVERSION "0" LINK_INTERFACE_LIBRARIES "" DEFINE_SYMBOL BUILDING_PRISON)

set(LIB_SUFFIX "" CACHE STRING "Define suffix of directory name (32/64)" )

install( TARGETS prison DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX} )

install( FILES
         abstractbarcodeitem.h
	 AbstractBarcodeItem
	 abstractbarcodewidget.h
	 AbstractBarcodeWidget
	 datamatriximage.h
	 DataMatrixImage
	 datamatrixitem.h
	 DataMatrixItem
	 datamatrixwidget.h
	 DataMatrixWidget
	 qrcodeimage.h
	 QRCodeImage
	 qrcodeitem.h
	 QRCodeItem
	 qrcodewidget.h
	 QRCodeWidget
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


