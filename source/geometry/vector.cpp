#include "vector.hpp"
#include "custom_assert.hpp"

using namespace geometry;


vector_t::vector_t(double x, double y, double z) : x_(x), y_(y), z_(z) {}

vector_t::vector_t(const point_t &pnt) : x_(pnt.get_x()), y_(pnt.get_y()), z_(pnt.get_z()) {}


bool vector_t::is_valid() const { return (std::isfinite(x_) && std::isfinite(y_) && std::isfinite(z_)); }


bool vector_t::operator== (const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return (is_equal(x_, vec2.x_) && is_equal(y_, vec2.y_) && is_equal(z_, vec2.z_));
}


bool vector_t::operator!= (const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return !(is_equal(x_, vec2.x_) && is_equal(y_, vec2.y_) && is_equal(z_, vec2.z_));
}


vector_t vector_t::operator- (const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return vector_t{x_ - vec2.x_, y_ - vec2.y_, z_ - vec2.z_};
}


vector_t vector_t::operator+ (const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return vector_t{x_ + vec2.x_, y_ + vec2.y_, z_ + vec2.z_};
}


vector_t vector_t::vec_product(const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return vector_t{y_ * vec2.z_ - z_ * vec2.y_,
                    z_ * vec2.x_ - x_ * vec2.z_,
                    x_ * vec2.y_ - y_ * vec2.x_};
}


double vector_t::get_squared_len() const
{
    ASSERT(is_valid());

    return x_*x_ + y_*y_ + z_*z_;
}


vector_t vector_t::normalized() const
{
    ASSERT(is_valid());

    double len = std::sqrt(get_squared_len());
    if (is_equal(len, 0))
        return *this;

    return vector_t{x_/len, y_/len, z_/len};
}


void vector_t::print() const
{
    std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")" << std::endl;
}


double vector_t::sqal_product(const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return x_*vec2.x_ + y_*vec2.y_ + z_*vec2.z_;
}


double vector_t::get_x() const { return x_; }
double vector_t::get_y() const { return y_; }
double vector_t::get_z() const { return z_; }