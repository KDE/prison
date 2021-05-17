add_executable(test-prison)
target_sources(test-prison PRIVATE prison.cpp barcodeexamplewidget.cpp main.cpp)
target_link_libraries(test-prison Qt5::Widgets KF5::Prison)
