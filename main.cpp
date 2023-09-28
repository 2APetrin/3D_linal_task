#include "geometry/triangle/triangle.hpp"
#include "geometry/point/point.hpp"
#include "geometry/vector/vector.hpp"
#include <iostream>

using namespace geometry;

int main()
{
    point_t p1(-0.5, 0, 0);
    point_t p2(-0.5, 1, 0);
    point_t p3(-3, 0, 2);
    point_t a1(0,4,1);
    point_t a2(0,-1,1);
    point_t a3(-2,-1,1);

    triangle_t t1{p1, p2, p3},
               t2{a1, a2, a3};

    if (t1.intersects(t2)) std::cout << "\npobeda" << std::endl;
        std::cout << "\nporajenie" << std::endl;

    return 0;
}