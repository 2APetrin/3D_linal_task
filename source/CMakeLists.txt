cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(triag double_operations.cpp point.cpp plane.cpp
               vector.cpp line.cpp segment.cpp triangle.cpp ../main.cpp)