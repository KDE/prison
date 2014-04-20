
set(prison_SRCS prison.cpp main.cpp)
add_executable(test-prison ${prison_SRCS})
target_link_libraries(test-prison ${QT_QTGUI_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} prison)
