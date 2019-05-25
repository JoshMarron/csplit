add_executable(csplitcore.t.tsk
               csplitcore.t.cpp
               split.t.cpp)           

find_package(GTest MODULE REQUIRED)
find_package(GMock MODULE REQUIRED)
find_package(spdlog CONFIG REQUIRED)
target_link_libraries(csplitcore.t.tsk PRIVATE GTest::GTest GMock::GMock spdlog::spdlog csplitcore)
target_include_directories(csplitcore.t.tsk PRIVATE 
                           ${PROJECT_SOURCE_DIR}/src 
                           ${PROJECT_SOURCE_DIR}/include)