add_library(csplitcore timer.cpp
                        timerutils.cpp)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(csplitcore PRIVATE spdlog::spdlog)