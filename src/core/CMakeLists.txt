add_library(csplitcore timer.cpp
                       timerutils.cpp
                       split.cpp)

find_package(spdlog CONFIG REQUIRED)
target_include_directories(csplitcore PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(csplitcore PRIVATE spdlog::spdlog)
target_compile_features(csplitcore PUBLIC cxx_std_17)