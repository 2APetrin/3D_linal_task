#include "triangle.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "octree.hpp"
#include <iostream>
#include <vector>
#include <array>
#include "chrono"
#include <set>

using namespace geometry;

int main()
{
    int triag_num = 0;
    if (triag_num < 0)
    {
        std::cout << "nuber of triags can't be negative" << std::endl;
        return -1;
    }

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

    //const std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

    octrees::octree_t octree(triags);
    //std::cout << "TREE CONSTRUCTED\n";

    /* const auto octree_end = std::chrono::high_resolution_clock::now();
    std::cout << "octree time = " << std::chrono::duration_cast<std::chrono::milliseconds>(octree_end - start).count() / 1000.0 << std::endl; */

    std::vector<bool> answer;
    answer.reserve(triag_num);

    for (int i = 0; i < triag_num; i++)
        answer[i] = false;

    octree.get_collisions(answer);

    /* const auto end = std::chrono::high_resolution_clock::now();
    const auto mk_s = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    const double s = mk_s / 1000.0; */

    for (int i = 0; i < triag_num; i++)
        if(answer[i]) std::cout << i << std::endl;

    //std::cout << "all time in sec - " << s << std::endl;

    return 0;
}