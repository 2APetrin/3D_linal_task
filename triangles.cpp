#include "include/triangles.hpp"


int main()
{
    triags::point_t A{3, 4, -2}, B{2, 4, 0}, C{1, 4, 1}, D{1, 1, 1}, E{1, 6, 2}, F{1, 2, 0};

    std::cout << (A == B) << " and " << (B != C) << std::endl;

    triags::vector_t a{A}, b{B}, c{(a - b)};

    triags::triangle_t triag1{A, B, C};
    triags::triangle_t triag2{D, E, F};

    std::cout << std::endl << "bool = " << triag1.intersects(triag2) << std::endl;

    return 0;
}