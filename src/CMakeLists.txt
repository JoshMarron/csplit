add_executable(csplit
               csplit.m.cpp)
               
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(csplit PRIVATE spdlog::spdlog csplit_core)