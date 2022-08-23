cmake_minimum_required(VERSION 3.21)
project(lab6)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 23)

add_executable(lab6 main.cpp Polynomial.h)
target_link_libraries(lab6 gtest)
