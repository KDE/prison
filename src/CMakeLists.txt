add_subdirectory(lib)
add_subdirectory(tools)
if(TARGET Qt${QT_MAJOR_VERSION}::Quick)
    add_subdirectory(quick)
endif()

ecm_qt_install_logging_categories(
    EXPORT PRISON
    FILE prison.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)
