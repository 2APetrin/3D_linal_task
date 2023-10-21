cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(triag geometry/point.cpp geometry/plane.cpp
               geometry/vector.cpp geometry/line.cpp geometry/segment.cpp geometry/triangle.cpp ../main.cpp)