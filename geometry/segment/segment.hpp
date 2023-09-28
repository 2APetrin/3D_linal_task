#pragma once

#include "../line/line.hpp"

namespace geometry {

class segment_t
{
    point_t  first_;
    point_t  second_;

    vector_t dir_vec_{vector_t{second_} - vector_t{first_}};
    line_t   seg_line_{dir_vec_, first_};

    bool contains_inter_pnt(const point_t &pnt) const;

    public:

    bool contains_inter_seg(const segment_t &seg2) const;

    segment_t(const point_t &first, const point_t &second);

    bool is_valid() const;

    point_t intersect_line(const line_t &line) const;

    bool intersects_seg(const segment_t &seg2) const;
};

}