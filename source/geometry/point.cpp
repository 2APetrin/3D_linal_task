#include "point.hpp"
#include "custom_assert.hpp"
#include "double_operations.hpp"

using namespace geometry;


point_t::point_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}
point_t::point_t(const point_t &pnt) : x_(pnt.x_), y_(pnt.y_), z_(pnt.z_) {}

bool point_t::is_valid() const
{
    return (std::isfinite(x_) && std::isfinite(y_) && std::isfinite(z_));
}

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

void point_t::print() const
{
    ASSERT(is_valid());
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
}


bool point_t::special_check() const
{
    return (!std::isfinite(x_)) && std::isfinite(y_) && std::isfinite(z_);
}

double point_t::get_x() const { return x_; }
double point_t::get_y() const { return y_; }
double point_t::get_z() const { return z_; }