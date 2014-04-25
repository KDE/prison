project(prison)
cmake_minimum_required(VERSION 2.8.8 FATAL_ERROR)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(QRencode REQUIRED)
find_package(Dmtx REQUIRED)

# Enable CMake's Automoc
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

option(QT5_BUILD "Build libprison using the Qt5 framework" FALSE)


include_directories(${CMAKE_SOURCE_DIR}/lib ${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )

#### Qt 4 and 5 ####
if(QT5_BUILD)
  find_package(Qt5Core REQUIRED)
  find_package(Qt5Gui REQUIRED)
  find_package(Qt5Widgets REQUIRED)
  find_package(Qt5Test REQUIRED)

  include("cmake/modules/ECMQt4To5Porting.cmake")
  include_directories(${QT_INCLUDES}) # TODO: Port away from this.

  if(CMAKE_VERSION VERSION_LESS 2.8.9)
    message(FATAL_ERROR "Akonadi Qt 5 build requires at least CMake version 2.8.9")
  endif()

  if (Qt5_POSITION_INDEPENDENT_CODE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
  endif()

  set(QT_QTTEST_LIBRARIES Qt5::Test)
else()
  set(QT_USE_IMPORTED_TARGETS TRUE) # Qt 4 only
  set(QT_MIN_VERSION 4.8.0)         # Qt 4 only

  find_package(Qt4 REQUIRED)
  include(${QT_USE_FILE})
endif()



add_subdirectory(lib)
add_subdirectory(testapp)

add_subdirectory(tools)
