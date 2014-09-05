
find_package(Qt5 COMPONENTS Widgets)
set(prison_SRCS prison.cpp barcodeexamplewidget.cpp main.cpp)
add_executable(test-prison ${prison_SRCS})
target_link_libraries(test-prison Qt5::Widgets prison)
