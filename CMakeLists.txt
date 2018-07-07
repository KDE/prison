cmake_minimum_required(VERSION 3.0)

set(KF5_VERSION "5.48.0") # handled by release scripts
project(prison VERSION ${KF5_VERSION})

# ECM setup
include(FeatureSummary)
find_package(ECM 5.48.0 NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://projects.kde.org/projects/kdesupport/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${ECM_MODULE_PATH}")
cmake_policy(SET CMP0063 NEW)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMAddQch)
include(ECMAddTests)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

set(REQUIRED_QT_VERSION 5.8.0)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Gui)
find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG OPTIONAL_COMPONENTS Quick)
find_package(QRencode)
set_package_properties(QRencode PROPERTIES TYPE REQUIRED)
find_package(Dmtx)
set_package_properties(Dmtx PROPERTIES TYPE RECOMMENDED)

if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

ecm_setup_version(PROJECT VARIABLE_PREFIX PRISON
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/prison_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfigVersion.cmake"
                        SOVERSION 5
)

add_subdirectory(src)
if(BUILD_TESTING)
    find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test Widgets)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Prison")

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF5Prison_QCH
        FILE KF5PrisonQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5PrisonQchTargets.cmake\")")
endif()

configure_package_config_file(
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

# contains list of debug categories, for kdebugsettings
install(FILES prison.categories DESTINATION ${KDE_INSTALL_CONFDIR})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
