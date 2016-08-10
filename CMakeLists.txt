cmake_minimum_required(VERSION 2.8.12)

project(prison)

# ECM setup
include(FeatureSummary)
find_package(ECM 5.24.0  NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH "${ECM_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

set(REQUIRED_QT_VERSION "5.4.0")
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Gui)
find_package(QRencode REQUIRED)
find_package(Dmtx REQUIRED)

if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

set(KF5_VERSION "5.25.0") # handled by release scripts
ecm_setup_version(${KF5_VERSION} VARIABLE_PREFIX PRISON
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/prison_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfigVersion.cmake"
                        SOVERSION 5
)

include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(lib)
add_subdirectory(tools)
if(BUILD_TESTING)
    find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test Widgets)
    add_subdirectory(tests)
endif()

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Prison")
ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5PrisonConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5PrisonTargets
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  FILE KF5PrisonTargets.cmake
  NAMESPACE KF5::
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/prison_version.h
  DESTINATION ${KF5_INCLUDE_INSTALL_DIR}
  COMPONENT Devel
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
