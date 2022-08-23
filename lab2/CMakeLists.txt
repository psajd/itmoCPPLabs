cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lcurl")
set(CMAKE_CXX_STANDARD 23)

add_executable(untitled src/main.cpp include/json/json.hpp include/map/MyMap.h include/bprinter/impl/table_printer.tpp.h include/bprinter/table_printer.h
        src/table_printer.cpp)
target_link_libraries(untitled curl)