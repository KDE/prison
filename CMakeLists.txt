cmake_minimum_required(VERSION 3.27)

set(KF_VERSION "6.24.0") # handled by release scripts
project(prison VERSION ${KF_VERSION})

# ECM setup
include(FeatureSummary)
find_package(ECM 6.23.0 NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${ECM_MODULE_PATH}")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEGitCommitHooks)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGenerateExportHeader)
include(ECMAddTests)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)
include(ECMDeprecationSettings)
include(ECMGenerateQDoc)

set(EXCLUDE_DEPRECATED_BEFORE_AND_AT 0 CACHE STRING "Control the range of deprecated API excluded from the build [default=0].")

set(REQUIRED_QT_VERSION 6.8.0)

option(WITH_DMTX "Build with DataMatrix generation support" ON)
option(WITH_ZXING "Build with barcode scanning and PDF417 generation support" ON)
option(WITH_QUICK "Build QtQuick components" ON)
option(WITH_MULTIMEDIA "Build scanner support" ON)

find_package(Qt6 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Gui)

if (WITH_QUICK)
    include(ECMQmlModule)
    find_package(Qt6 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Quick)
endif()

if (WITH_MULTIMEDIA)
    find_package(Qt6 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Multimedia)
endif()

find_package(QRencode)
set_package_properties(QRencode PROPERTIES
    PURPOSE "Required for generation of QRCode barcodes."
    TYPE REQUIRED)
if (WITH_DMTX)
    find_package(Dmtx)
    set_package_properties(Dmtx PROPERTIES
        PURPOSE "Required for generation of Data Matrix barcodes."
        TYPE REQUIRED)
endif()
if (WITH_ZXING)
    foreach(ver 3.0 2.0 1.2.0)
        find_package(ZXing ${ver} CONFIG QUIET)
        if (TARGET ZXing::ZXing)
            break()
        endif()
    endforeach()
    set_package_properties(ZXing PROPERTIES
        PURPOSE "Required for generation of PDF417 barcodes and for scanning of barcodes from live video feed."
        TYPE REQUIRED)
endif()

ecm_setup_version(PROJECT VARIABLE_PREFIX PRISON
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/prison_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6PrisonConfigVersion.cmake"
                        SOVERSION 6
)
ecm_set_disabled_deprecation_versions(
    QT 6.11
)

add_subdirectory(src)
if(BUILD_TESTING)
    find_package(Qt6 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test Concurrent Widgets)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6Prison")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF6PrisonConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF6PrisonConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF6PrisonConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF6PrisonConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF6PrisonTargets
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  FILE KF6PrisonTargets.cmake
  NAMESPACE KF6::
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/prison_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Prison
  COMPONENT Devel
)

include(ECMFeatureSummary)
ecm_feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
