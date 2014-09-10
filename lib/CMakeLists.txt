

set(PRISON_VERSION "1.2.0")

ecm_setup_version(${PRISON_VERSION} VARIABLE_PREFIX PRISON
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/prison_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5PrisonConfigVersion.cmake"
                        SOVERSION 1
)


add_subdirectory(prison)
