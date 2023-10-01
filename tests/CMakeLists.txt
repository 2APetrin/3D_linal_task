cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(test_main test.cpp ../include/double_operations/double_operations.cpp
               ../geometry/point/point.cpp ../geometry/vector/vector.cpp
               ../geometry/line/line.cpp ../geometry/segment/segment.cpp
               ../geometry/plane/plane.cpp ../geometry/triangle/triangle.cpp)

target_link_libraries(test_main PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(test_main)