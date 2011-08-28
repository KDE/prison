project(prison)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(Qt4 REQUIRED)
find_package(QRencode REQUIRED)
find_package(Dmtx REQUIRED)


include_directories(${CMAKE_SOURCE_DIR}/lib ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )


add_subdirectory(lib)
add_subdirectory(testapp)

add_subdirectory(tools)