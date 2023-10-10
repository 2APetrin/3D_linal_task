#pragma once

#include "double_operations.hpp"
#include "segment.hpp"
#include "plane.hpp"

namespace geometry {

const double bound_coeff = 0.36; // it's min coeff squared (0.6 * 0.6) to bound triangles by it's longest segment

class triangle_t
{
    point_t   A_, B_, C_;

    bool is_in_triag(const point_t &pnt) const;

    bool check_triags_in_intersect_planes(const triangle_t &triag2, const plane_t &pln1, const plane_t &pln2) const;

    bool check_triags_in_same_plane(const triangle_t &triag2) const;

    segment_t get_triag_intersection(const line_t &line) const;

    vector_t get_center_vec_x3() const;

    double get_bounding_sphere_radius(const triangle_t &triag2) const;

    public:

    plane_t get_plane() const;

    triangle_t(const point_t &A, const point_t &B, const point_t &C);

    bool is_valid() const;

    bool check_triag_intersect_plane(const triangle_t &triag2, const plane_t &pln1, const plane_t &pln2) const;

    void print() const;

    bool intersects(const triangle_t &triag2) const;

    point_t getA() const;
    point_t getB() const;
    point_t getC() const;
};

}