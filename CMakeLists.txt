cmake_minimum_required(VERSION 3.16)

set(KF_VERSION "5.103.0") # handled by release scripts
project(prison VERSION ${KF_VERSION})

# ECM setup
include(FeatureSummary)
find_package(ECM 5.103.0 NO_MODULE)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://commits.kde.org/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${ECM_MODULE_PATH}")
cmake_policy(SET CMP0063 NEW)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEGitCommitHooks)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGenerateExportHeader)
include(ECMGeneratePriFile)
include(ECMAddQch)
include(ECMAddTests)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)
include(ECMQmlModule)
include(ECMDeprecationSettings)

set(EXCLUDE_DEPRECATED_BEFORE_AND_AT 0 CACHE STRING "Control the range of deprecated API excluded from the build [default=0].")

option(BUILD_QCH "Build API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)" OFF)
add_feature_info(QCH ${BUILD_QCH} "API documentation in QCH format (for e.g. Qt Assistant, Qt Creator & KDevelop)")

set(REQUIRED_QT_VERSION 5.15.2)
find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core Gui)
find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG OPTIONAL_COMPONENTS Quick Multimedia)
find_package(QRencode)
set_package_properties(QRencode PROPERTIES
    PURPOSE "Required for generation of QRCode barcodes."
    TYPE REQUIRED)
find_package(Dmtx)
set_package_properties(Dmtx PROPERTIES
    PURPOSE "Required for generation of Data Matrix barcodes."
    TYPE RECOMMENDED)
find_package(ZXing 2.0)
if (NOT TARGET ZXing::ZXing)
  find_package(ZXing 1.2.0)
endif()
set_package_properties(ZXing PROPERTIES
    PURPOSE "Required for generation of PDF417 barcodes and for scanning of barcodes from live video feed."
    TYPE RECOMMENDED)

if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

ecm_setup_version(PROJECT VARIABLE_PREFIX PRISON
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/prison_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfigVersion.cmake"
                        SOVERSION 5
)
ecm_set_disabled_deprecation_versions(
    QT 5.15.2
)

add_subdirectory(src)
if(BUILD_TESTING)
    find_package(Qt${QT_MAJOR_VERSION} ${REQUIRED_QT_VERSION} CONFIG REQUIRED Test Widgets)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5Prison")

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
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Prison
  COMPONENT Devel
)

# TODO KF6: remove this, kept for backwards-compatibility in KF5 so that #inlcude <prison/prison_version.h>
# continues working
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/prison_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/Prison/prison
  COMPONENT Devel
)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

kde_configure_git_pre_commit_hook(CHECKS CLANG_FORMAT)
