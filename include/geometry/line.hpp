#pragma once

#include "vector.hpp"

namespace geometry {

class line_t
{
    vector_t dir_vec_;
    point_t  line_pnt_;

    double p1_, p2_, p3_;

    public:

    line_t(const vector_t &dir_vec, const point_t &line_pnt);

    bool operator== (const line_t &line2) const;

    bool is_valid() const;

    bool check_point_belong(const point_t &pnt) const;

    point_t  get_line_intersection(const line_t &line2) const;

    point_t  get_line_pnt() const;

    vector_t get_dir_vec() const;

    void print() const;
};

}
