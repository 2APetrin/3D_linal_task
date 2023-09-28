#pragma once

#include "../../include/double_operations/double_operations.hpp"
#include <cmath>

namespace geometry {

enum mutual_pos
{
    INTERSECT,
    PARALLEL,
    EQUAL
};

class point_t
{
    double x_, y_, z_;

    public:

    point_t(double x = NAN, double y = NAN, double z = NAN);
    point_t(const point_t &pnt);

    bool is_valid() const;

    bool operator== (const point_t &pnt) const;

    bool operator!= (const point_t &pnt) const;

    void print() const;



    double get_x() const;
    double get_y() const;
    double get_z() const;
};

}