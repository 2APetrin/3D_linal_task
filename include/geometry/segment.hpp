#pragma once

#include "line.hpp"
#include "plane.hpp"

namespace geometry {

class segment_t
{
    point_t first_;
    point_t second_;

    vector_t dir_vec_{vector_t{second_} - vector_t{first_}};

    line_t seg_line_{dir_vec_, first_};

    public:

    /**
     * \brief works correctly only if components are lying in the same plane
    */
    bool contains_inter_pnt(const point_t &pnt) const;

    segment_t(const point_t &first, const point_t &second);

    bool is_valid() const;

    /**
     * \brief works correctly only if segments are lying on the same line
    */
    bool contains_inter_seg(const segment_t &seg2) const;

    /**
     * \brief works correctly only if segments are lying in the same plane
    */
    bool intersects_seg(const segment_t &seg2) const;

    /**
     * \brief works correctly only if components are lying in the same plane
    */
    point_t get_line_intersection(const line_t &line) const;

    point_t get_plane_intersection(const plane_t &pln) const;

    vector_t get_dir_vec() const;

    line_t get_seg_line() const;
};

}