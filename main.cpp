#include "geometry/triangle/triangle.hpp"
#include "geometry/point/point.hpp"
#include "geometry/vector/vector.hpp"
#include <iostream>
#include <vector>
#include <set>

using namespace geometry;

int main()
{
    int triag_num = 0;
    std::cin >> triag_num;
    std::vector<triangle_t> triags;
    if (triag_num > 0)
    {
        for (int i = 0; i < triag_num; i++)
        {
            double a = 0, b = 0, c = 0;
            std::cin >> a >> b >> c;
            point_t p1{a, b, c};
            std::cin >> a >> b >> c;
            point_t p2{a, b, c};
            std::cin >> a >> b >> c;
            point_t p3{a, b, c};

            triags.push_back(triangle_t{p1, p2, p3});
        }
    }
    else
        std::cerr << "Triangle number should be greater than 0" << std::endl;

    std::set<int> number_set;
    for (int i = 0; i < triag_num; i++)
    {
        for (int j = i + 1; j < triag_num; j++)
        {
            if (i != j)
                if (triags[i].intersects(triags[j]))
                {
                    number_set.insert(i+1);
                    number_set.insert(j+1);
                }
        }
    }

    for (auto it = number_set.begin(); it != number_set.end(); it++)
    {
        std::cout << *it << " ";
    }

    return 0;
}