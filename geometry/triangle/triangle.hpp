#pragma once

#include "../plane/plane.hpp"
#include "../segment/segment.hpp"

namespace geometry {

class triangle_t
{
    point_t  A_, B_, C_;
    vector_t norm_vec_{(vector_t{B_} - vector_t{A_}).vec_product(vector_t{C_} - vector_t{A_})};
    plane_t  plane_{norm_vec_, A_};
    segment_t AB_{A_, B_}, BC_{B_, C_}, CA_{C_, A_};

    bool check_triag_intersect_plane(const triangle_t &triag2) const;

    bool check_triags_in_intersect_planes(const triangle_t &triag2) const;

    bool check_triags_in_same_plane(const triangle_t &triag2) const;

    bool is_in_triag(const point_t &pnt) const;

    segment_t get_triag_intersection(const line_t &line) const;

    public:

    triangle_t(const point_t &A, const point_t &B, const point_t &C);

    bool is_valid() const;

    void print() const;

    bool intersects(const triangle_t &triag2) const;
};

}