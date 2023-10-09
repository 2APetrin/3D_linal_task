#include "triangle.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "octree.hpp"
#include <iostream>
#include <vector>
#include "chrono"
#include <set>

using namespace geometry;

int main()
{
    int triag_num = 0;
    std::cin >> triag_num;
    std::vector<octrees::triag_id_t> triags;
    if (triag_num > 0)
    {
        for (size_t i = 0; i < triag_num; i++)
        {
            double a = 0, b = 0, c = 0;
            std::cin >> a >> b >> c;
            point_t p1{a, b, c};
            std::cin >> a >> b >> c;
            point_t p2{a, b, c};
            std::cin >> a >> b >> c;
            point_t p3{a, b, c};

            triags.push_back(octrees::triag_id_t{triangle_t{p1, p2, p3}, i});
        }
    }
    else
        std::cerr << "Triangle number should be greater than 0" << std::endl;

    std::set<int> number_set;

    octrees::octree_t octree(triags);

    return 0;
}