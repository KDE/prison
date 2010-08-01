
include_directories(${CMAKE_SOURCE_DIR}/lib ${CMAKE_CURRENT_BINARY_DIR})

set(prison_SRCS prison.cpp main.cpp)
qt4_automoc(${prison_SRCS})
add_executable(test-prison ${prison_SRCS})
target_link_libraries(test-prison ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} prison)
