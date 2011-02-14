
find_package(Qt4 COMPONENTS QtGui QtCore REQUIRED)

add_executable(prison-datamatrix prison-datamatrix.cpp)
target_link_libraries(prison-datamatrix prison ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY})
