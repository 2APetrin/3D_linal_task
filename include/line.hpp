#pragma once

#include "vector.hpp"

namespace geometry {

class line_t
{
    vector_t dir_vec_;
    point_t  line_pnt_;

    public:

    line_t(const vector_t &dir_vec, const point_t &line_pnt);

    bool operator== (const line_t &line2) const;

    bool is_valid() const;

    bool check_point_belong(const point_t &pnt) const;

    point_t  get_line_intersection_same_plane(const line_t &line2) const;

    vector_t get_dir_vec() const;

    void     print() const;
};

}
