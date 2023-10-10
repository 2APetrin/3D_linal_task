#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "triangle.hpp"
#include "vector.hpp"

using namespace std;
using namespace geometry;

TEST(point_test, basic_pnt)
{
    point_t p1{1, 2, 3};
    point_t p2{1.0000001, 2, 3};
    point_t p3{1.0001, 2, 3};


    ASSERT_TRUE(p1.is_valid());
    ASSERT_TRUE(p2.is_valid());
    ASSERT_TRUE(p3.is_valid());
    ASSERT_TRUE(p1 == p2);
    ASSERT_FALSE(p1 == p3);
}

TEST(vec_test, basic_vec)
{
    vector_t v1{{0, 0, 0}};
    vector_t v2{{1, 1, 1}};
    vector_t v3{{-1, -1, -1}};

    ASSERT_TRUE((v1 + v2 + v3) == v1);
    ASSERT_TRUE((v1 + v2 - v3) == (v2 + v2));
    ASSERT_TRUE(v2.vec_product(v3) == v1);
}

TEST(plane_test, basic_plane)
{
    plane_t pln1{{{1, 0, 1}},  {1, -3, 2}};
    plane_t pln2{{{-2, 0, 1}}, {1, -3, 2}};
    line_t  ln12 = {{{0, 1, 0}}, {1, 0 , 2}};
    ASSERT_TRUE(pln1.get_intersection(pln2) == ln12);

    plane_t pln3{{{0, 1 , 1}}, {1, 1, 1}};
    plane_t pln4{{{0, 0, 1}}, {0, 0, 0}};
    line_t  ln34{{{-1, 0, 0}}, {0, 2, 0}};
    ASSERT_TRUE(pln3.get_intersection(pln4) == ln34);

    plane_t pln5{{{0, 0, 1}}, {1, 1, 1}};
    plane_t pln6{{{0, 0, 1}}, {0, 0, 0}};
    ASSERT_FALSE(pln5.get_intersection(pln6).is_valid());

    plane_t pln7{{{0, 0, 1}}, {1, 1, 1}};
    plane_t pln8{{{0, 0, 1}}, {0, 0, 1}};
    ASSERT_FALSE(pln7.get_intersection(pln8).is_valid());
}

TEST(triangle_test, triangle_basic)
{
    triangle_t tr1{{0, 0, 0}, {1, 0, 0}, {0, 1, 0}};
    triangle_t tr2{{0.5, 0.5, 0}, {1.5, 0.5, 0}, {1, 1, 0}};
    ASSERT_TRUE(tr1.intersects(tr2));

    triangle_t tr3{{0.5, 0.5, 0}, {1.5, 0.5, 0}, {0.5, 0.5, 1}};
    ASSERT_TRUE(tr1.intersects(tr3));

    triangle_t tr4{{0.25, 0.25, 0}, {0.5, 0, 0}, {0, 0.5, 0}};
    ASSERT_TRUE(tr4.get_plane().is_valid());
    ASSERT_TRUE(tr1.intersects(tr4));

    triangle_t tr5{{0.25, 0.25, 1}, {0.5, 0, 1}, {0, 0.5, 1}};
    ASSERT_FALSE(tr1.intersects(tr5));

    triangle_t tr6{{0.25, 0.25, 0.5}, {0.5, 0, 1}, {0, 0.5, 1}};
    ASSERT_FALSE(tr1.intersects(tr6));

    triangle_t tr7{{0.25, 0.25, -0.5}, {0.5, 0, 1}, {0, 0.5, 1}};
    ASSERT_TRUE(tr1.intersects(tr7));
}

TEST(bad_plane, pln_test)
{
    triangle_t t001({-3078.3, -8662.3, 9288.5}, {-3116.2, -8620.4, 9264.1}, {-3107.9, -8635, 9274.9});

    ASSERT_TRUE(t001.get_plane().is_valid());
}

TEST(bad_triag, tr_test)
{
    triangle_t t001({-3078.3, -8662.3, 9288.5}, {-3116.2, -8620.4, 9264.1}, {-3107.9, -8635, 9274.9});
    triangle_t t002({-3017.4, -8572.8, 9388.3}, {-3004, -8533.7, 9351.3}, {-3128.9, -8635.9, 9252.9});

    ASSERT_TRUE(t001.intersects(t002));

    triangle_t t3({0,0,0}, {100, 0,0}, {100, 1, 0});
    triangle_t t4({1, -1, -1}, {1, 0,1}, {1, 1, -1});

    ASSERT_TRUE(t3.intersects(t4));
    ASSERT_TRUE(t4.intersects(t3));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}