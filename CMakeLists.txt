project(prison)
cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(Qt4 REQUIRED)
find_package(QRencode REQUIRED)
find_package(Dmtx REQUIRED)

# Enable CMake's Automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories(${CMAKE_SOURCE_DIR}/lib ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )


add_subdirectory(lib)
add_subdirectory(testapp)

add_subdirectory(tools)
