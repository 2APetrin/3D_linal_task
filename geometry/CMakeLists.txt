cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(main_triag point/point.cpp vector/vector.cpp line/line.cpp
               segment/segment.cpp plane/plane.cpp plane/plane.cpp triangle/triangle.cpp
               ../include/double_operations/double_operations.cpp ../main.cpp)

