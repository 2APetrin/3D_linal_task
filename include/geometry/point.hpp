#pragma once

#include "double_operations.hpp"
#include <cmath>

namespace geometry {

class point_t
{
    double x_, y_, z_;

    public:

    point_t(double x = NAN, double y = NAN, double z = NAN);

    bool is_valid() const;

    bool operator== (const point_t &pnt) const;

    bool operator!= (const point_t &pnt) const;

    bool special_check() const;

    void print() const;

    double get_x() const;
    double get_y() const;
    double get_z() const;
};

const point_t NAN_PNT  = {NAN, NAN, NAN};
const point_t SPEC_PNT = {NAN, 0, 0};
const point_t NULL_PNT = {0, 0, 0};

}