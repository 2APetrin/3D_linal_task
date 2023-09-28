#pragma once

#include "../../include/double_operations/double_operations.hpp"
#include "../point/point.hpp"

namespace geometry {

class vector_t
{
    point_t cords_;

    public:

    vector_t(const point_t  &pnt_cords);
    vector_t(const vector_t &vec);

    bool operator== (const vector_t &vec2) const;
    bool operator!= (const vector_t &vec2) const;

    vector_t operator- (const vector_t &vec2) const;
    vector_t operator+ (const vector_t &vec2) const;

    bool is_valid() const;

    vector_t vec_product(const vector_t &vec2) const;

    void print() const;



    double get_x() const;
    double get_y() const;
    double get_z() const;
};

}
