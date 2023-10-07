cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(test_main test.cpp ../source/double_operations.cpp
               ../source/point.cpp ../source/vector.cpp
               ../source/line.cpp ../source/segment.cpp
               ../source/plane.cpp ../source/triangle.cpp)

target_link_libraries(test_main PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(test_main)