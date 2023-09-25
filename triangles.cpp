#include "include/triangles.hpp"


int main()
{
    triags::point_t A{1, 0, 0}, B{0, 1, 0}, C{0, 0, 1};

    std::cout << (A == B) << " and " << (B != C) << std::endl;

    triags::vector_t a{A}, b{B}, c{(a - b)};
    c.print();

    triags::triangle_t triag1{A, B, C};
    triags::triangle_t triag2{A, C, B};
    triag1.print();
    triag2.print();

    return 0;
}