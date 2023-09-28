#include "vector.hpp"
#include "../../include/custom_assert.hpp"

using namespace geometry;


vector_t::vector_t(const point_t  &pnt_cords) : cords_(pnt_cords) {}
vector_t::vector_t(const vector_t &vec) : cords_(point_t{vec.get_x(), vec.get_y(), vec.get_z()}) {}

bool vector_t::operator== (const vector_t &vec2) const { return cords_ == vec2.cords_; }
bool vector_t::operator!= (const vector_t &vec2) const { return cords_ != vec2.cords_; }

vector_t vector_t::operator- (const vector_t &vec2) const
{
    return {{get_x() - vec2.get_x(), get_y() - vec2.get_y(), get_z() - vec2.get_z()}};
}

vector_t vector_t::operator+ (const vector_t &vec2) const
{
    return {{get_x() + vec2.get_x(), get_y() + vec2.get_y(), get_z() + vec2.get_z()}};
}

bool vector_t::is_valid() const { return cords_.is_valid(); }

vector_t vector_t::vec_product(const vector_t &vec2) const
{
    ASSERT(is_valid());
    ASSERT(vec2.is_valid());

    return {{get_y() * vec2.get_z() - get_z() * vec2.get_y(),
             get_z() * vec2.get_x() - get_x() * vec2.get_z(),
             get_x() * vec2.get_y() - get_y() * vec2.get_x()}};
}

void vector_t::print() const
{
    ASSERT(is_valid());
    std::cout << "(" << get_x() << ", " << get_y() << ", " << get_z() << ")" << std::endl;
}



double vector_t::get_x() const { return cords_.get_x(); }
double vector_t::get_y() const { return cords_.get_y(); }
double vector_t::get_z() const { return cords_.get_z(); }
