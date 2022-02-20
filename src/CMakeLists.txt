add_subdirectory(lib)
add_subdirectory(tools)
if(TARGET Qt${QT_MAJOR_VERSION}::Quick)
    add_subdirectory(quick)
endif()
if(TARGET Qt${QT_MAJOR_VERSION}::Multimedia AND TARGET ZXing::ZXing)
    add_subdirectory(scanner)
    if (TARGET Qt${QT_MAJOR_VERSION}::Quick)
        add_subdirectory(scanner-quick)
    endif()
endif()

ecm_qt_install_logging_categories(
    EXPORT PRISON
    FILE prison.categories
    DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
)
