#pragma once

#include <cmath>
#include <iostream>
#include "custom_assert.hpp"

const double eq_accuracy = 0.00001;

class line_t;
class triangle_t;
class plane_t;


class point_t
{
    double x = NAN, y = NAN, z = NAN;

    public:

    point_t(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    bool is_valid() const { return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z)); }

    bool equal(const point_t &pnt) const
    {
        ASSERT(is_valid());
        ASSERT(pnt.is_valid());

        return ((std::abs(x - pnt.x) < eq_accuracy) && (std::abs(y - pnt.y) < eq_accuracy) && (std::abs(z - pnt.z) < eq_accuracy));
    }

    void print() const
    {
        ASSERT(is_valid());
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    double get_x() const { return x; }
    double get_y() const { return y; }
    double get_z() const { return z; }
};


class vector_t
{
    point_t vec;

    public:
    vector_t(const point_t vec_point) : vec(vec_point) {}

    bool is_valid() const { return vec.is_valid(); }

    bool is_equal(vector_t second_vec) const { return vec.equal(second_vec.vec); }

    vector_t vec_prod(const vector_t second_vec) const
    {
        ASSERT(is_valid());
        ASSERT(second_vec.is_valid());

        point_t ret_vec{
            vec.get_y() * second_vec.vec.get_z() - vec.get_z() * second_vec.vec.get_y(),
            vec.get_z() * second_vec.vec.get_x() - vec.get_x() * second_vec.vec.get_z(),
            vec.get_x() * second_vec.vec.get_y() - vec.get_y() * second_vec.vec.get_x()
        };

        return {ret_vec};
    }

    void print() const
    {
        ASSERT(is_valid());
        std::cout << "(" << vec.get_x() << ", " << vec.get_y() << ", " << vec.get_z() << ")" << std::endl;
    }

    double get_x() const { return vec.get_x(); }
    double get_y() const { return vec.get_y(); }
    double get_z() const { return vec.get_z(); }
};


class line_t
{
    point_t  line_pnt;
    vector_t dir_vec;

    public:
    line_t(const point_t line_pnt_, const vector_t dir_vec_) : line_pnt(line_pnt_), dir_vec(dir_vec_) {}
};


class plane_t
{
    double a = NAN, b = NAN, c = NAN, d = NAN;

    vector_t norm_vec;
    point_t  plane_point;

    enum planes_pos
    {
        PLANE_INTERSECT = 0,
        PLANE_PARALLEL  = 1,
        PLANE_EQUAL     = 2
    };

    public:

    plane_t(vector_t &norm_vec_, point_t &plane_point_) : norm_vec(norm_vec_), plane_point(plane_point_)
    {
        ASSERT(norm_vec.is_valid());
        ASSERT(plane_point.is_valid());

        a = norm_vec.get_x();
        b = norm_vec.get_y();
        c = norm_vec.get_z();

        d = -1 * (a * plane_point.get_x() + b * plane_point.get_y() + c * plane_point.get_z());
    }

    void get_intesect(plane_t second_plane)
    {
        planes_pos pos_type = get_planes_pos(second_plane);

        if (!pos_type) return get_planes_intersection();

        std::cout << pos_type << std::endl;
    }

    planes_pos get_planes_pos(plane_t second_plane)
    {
        ASSERT(norm_vec.is_valid());
        ASSERT(second_plane.norm_vec.is_valid());

        vector_t line_vec = norm_vec.vec_prod(second_plane.norm_vec);
        if (!line_vec.is_equal(point_t{0, 0, 0}))
            return PLANE_INTERSECT;

        if (std::abs(d - second_plane.d) < eq_accuracy)
            return PLANE_EQUAL;

        return PLANE_PARALLEL;
    }

    void print() const
    {
        std::cout << "plane: " << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << std::endl;
    }
};


class triangle_t
{
    point_t A, B, C;
    plane_t triag_plane;

    public:
    bool intersect_check() const
    {
    }
};
