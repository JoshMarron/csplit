add_library(csplitcore timer.cpp
                       timerutils.cpp
                       split.cpp
                       speedrun.cpp
                       splitter.cpp
                       adhocsplitter.cpp
                       timeattacksplitter.cpp
                       )

find_package(spdlog CONFIG REQUIRED)
target_include_directories(csplitcore PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(csplitcore PUBLIC spdlog::spdlog)
target_compile_features(csplitcore PUBLIC cxx_std_17)