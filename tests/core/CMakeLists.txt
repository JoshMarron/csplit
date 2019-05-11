add_executable(csplitcore.t.tsk
               csplitcore.t.cpp
               split.t.cpp)           

find_package(GTest MODULE REQUIRED)
find_package(GMock MODULE REQUIRED)
target_link_libraries(csplitcore.t.tsk PRIVATE GTest::GTest GMock::GMock)