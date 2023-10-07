#pragma once

#include "double_operations.hpp"
#include "point.hpp"

namespace geometry {

class vector_t
{
    double x_, y_, z_;

    public:

    vector_t(double x = NAN, double y = NAN, double z = NAN);
    vector_t(const point_t  &pnt);
    vector_t(const vector_t &vec);

    bool is_valid() const;

    bool operator== (const vector_t &vec2) const;
    bool operator!= (const vector_t &vec2) const;

    vector_t operator- (const vector_t &vec2) const;
    vector_t operator+ (const vector_t &vec2) const;

    vector_t vec_product(const vector_t &vec2) const;

    double get_squared_len() const;

    vector_t normalized() const;


    void   print() const;
    double get_x() const;
    double get_y() const;
    double get_z() const;
};

}
