add_library(csplit_core timer.cpp)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(csplit_core PRIVATE spdlog::spdlog)