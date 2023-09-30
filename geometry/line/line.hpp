#pragma once

#include "../vector/vector.hpp"

namespace geometry {

class line_t
{
    vector_t dir_vec_;
    point_t  line_pnt_;

    double p1_ = dir_vec_.get_x();
    double p2_ = dir_vec_.get_y();
    double p3_ = dir_vec_.get_z();

    public:

    bool operator== (const line_t &line2) const;

    line_t(const vector_t &dir_vec, const point_t &line_pnt);

    bool is_valid() const;

    void print() const;

    point_t get_line_intersection(const line_t &line2) const;

    vector_t get_dir_vec() const;

    bool check_belong_point(const point_t &pnt) const;
};

}
