#include "double_operations.hpp"
#include "custom_assert.hpp"
#include "point.hpp"
#include <iostream>

using namespace geometry;
using namespace doperations;


bool point_t::operator== (const point_t &pnt) const
{
    ASSERT(is_valid());
    ASSERT(pnt.is_valid());

    return (is_equal(x_, pnt.x_) && is_equal(y_, pnt.y_) && is_equal(z_, pnt.z_));
}


bool point_t::operator!= (const point_t &pnt) const
{
    ASSERT(is_valid());
    ASSERT(pnt.is_valid());

    return !(is_equal(x_, pnt.x_) && is_equal(y_, pnt.y_) && is_equal(z_, pnt.z_));
}
