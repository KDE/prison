
set(PRISON_VERSION "1.2.2")

set(CMAKECONFIG_INSTALL_DIR "${CMAKECONFIG_INSTALL_PREFIX}/KF5Prison")

ecm_setup_version(${PRISON_VERSION} VARIABLE_PREFIX PRISON
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/prison_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfigVersion.cmake"
                        SOVERSION 1
)


ecm_configure_package_config_file(
  "${prison_SOURCE_DIR}/lib/KF5PrisonConfig.cmake.in"
  "${prison_BINARY_DIR}/lib/KF5PrisonConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${prison_BINARY_DIR}/lib/KF5PrisonConfig.cmake"
  "${prison_BINARY_DIR}/lib/KF5PrisonConfigVersion.cmake"
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


add_subdirectory(prison)
