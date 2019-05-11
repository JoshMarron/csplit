cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(csplit CXX)

include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(src)
add_subdirectory(src/core)

enable_testing()
add_subdirectory(tests)
add_subdirectory(tests/core)