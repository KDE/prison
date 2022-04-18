add_executable(prison-test)
target_sources(prison-test PRIVATE prisontest.cpp barcodeexamplewidget.cpp main.cpp)
target_link_libraries(prison-test Qt${QT_MAJOR_VERSION}::Widgets KF5::Prison)
