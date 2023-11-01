cmake_minimum_required(VERSION 3.8)

project(triangles LANGUAGES CXX)

add_executable(test_main test.cpp        ../src/geometry/vector.cpp
               ../src/geometry/line.cpp  ../src/geometry/segment.cpp
               ../src/geometry/plane.cpp ../src/geometry/triangle.cpp)

target_link_libraries(test_main PRIVATE ${GTEST_LIBRARIES})

gtest_discover_tests(test_main)