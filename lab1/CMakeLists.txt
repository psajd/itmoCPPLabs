cmake_minimum_required(VERSION 3.20)
project(lab1)

set(CMAKE_CXX_STANDARD 23)

add_executable(lab1 lab1/main.cpp lab1/Polynomial.h lab1/Point.cpp lab1/Point.h lab1/Polyline.cpp lab1/Polyline.h lab1/Closed_Polyline.cpp lab1/Closed_Polyline.h lab1/Polygon.cpp lab1/Polygon.h lab1/Regular_polygon.cpp lab1/Regular_polygon.h lab1/Triangle.cpp lab1/Triangle.h lab1/Trapeze.cpp lab1/Trapeze.h)
