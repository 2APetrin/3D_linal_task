#pragma once

#include "line.hpp"

namespace geometry {

class segment_t
{
    point_t first_;
    point_t second_;

    /**
     * \brief works only if components are lying in the same plane
    */
    bool contains_inter_pnt(const point_t &pnt) const;

    public:

    segment_t(const point_t &first, const point_t &second);

    bool is_valid() const;

    /**
     * \brief works only if segments are lying on the same line
    */
    bool contains_inter_seg(const segment_t &seg2) const;

    /**
     * \brief works only if segments are lying in the same plane
    */
    bool intersects_seg(const segment_t &seg2) const;

    /**
     * \brief works only if components are lying in the same plane
    */
    point_t intersect_line(const line_t &line) const;
};

}