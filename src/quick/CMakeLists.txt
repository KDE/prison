add_library(prisonquickplugin SHARED
    barcodequickitem.cpp
    prisonquickplugin.cpp
)
target_link_libraries(prisonquickplugin PRIVATE Qt5::Quick KF5::Prison)
install(TARGETS prisonquickplugin DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/prison)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/org/kde/prison)
