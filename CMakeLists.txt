project(prison)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(QRencode REQUIRED)
find_package(Dmtx REQUIRED)

# Enable CMake's Automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(${CMAKE_SOURCE_DIR}/lib ${CMAKE_CURRENT_BINARY_DIR} )

find_package(ECM 1.1.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
include(KDEInstallDirs)

set(QT_REQUIRED_VERSION "5.2.0")

find_package(Qt5Core ${QT_REQUIRED_VERSION} CONFIG  REQUIRED)
find_package(Qt5Gui ${QT_REQUIRED_VERSION} CONFIG  REQUIRED)
find_package(Qt5Test ${QT_REQUIRED_VERSION} CONFIG  REQUIRED)

if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

add_subdirectory(lib)
add_subdirectory(testapp)

add_subdirectory(tools)
