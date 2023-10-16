cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(test_main test.cpp ../source/double_operations.cpp
               ../source/geometry/point.cpp ../source/geometry/vector.cpp
               ../source/geometry/line.cpp ../source/geometry/segment.cpp
               ../source/geometry/plane.cpp ../source/geometry/triangle.cpp)

target_link_libraries(test_main PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(test_main)