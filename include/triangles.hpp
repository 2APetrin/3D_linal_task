#pragma once

#include <cmath>
#include <iostream>
#include "custom_assert.hpp"

const double ACCURACY = 0.00001;

namespace triags {

enum mutual_pos
{
    INTERSECT,
    PARALLEL,
    EQUAL
};

class point_t
{
    double x, y, z;

    public:

    point_t(double x_ = NAN, double y_ = NAN, double z_ = NAN) : x(x_), y(y_), z(z_) {}

    bool is_valid() const { return (std::isfinite(x) && std::isfinite(y) && std::isfinite(z)); }

    bool operator== (const point_t &pnt) const
    {
        ASSERT(is_valid());
        ASSERT(pnt.is_valid());

        return ((std::abs(x - pnt.x) < ACCURACY) && (std::abs(y - pnt.y) < ACCURACY) && (std::abs(z - pnt.z) < ACCURACY));
    }

    bool operator!= (const point_t &pnt) const
    {
        ASSERT(is_valid());
        ASSERT(pnt.is_valid());

        return !((std::abs(x - pnt.x) < ACCURACY) && (std::abs(y - pnt.y) < ACCURACY) && (std::abs(z - pnt.z) < ACCURACY));
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
    point_t cords;

    bool is_valid() const { return cords.is_valid(); }

    public:
    vector_t(const point_t  &pnt_coords) : cords(pnt_coords) {}
    vector_t(const vector_t &vec) : cords(point_t{vec.get_x(), vec.get_y(), vec.get_z()}) {}

    bool operator== (const vector_t &second_vec) const { return cords == second_vec.cords; }
    bool operator!= (const vector_t &second_vec) const { return cords != second_vec.cords; }

    vector_t operator- (const vector_t &second_vec) const{
        return {{cords.get_x() - second_vec.cords.get_x(), cords.get_y() - second_vec.cords.get_y(), cords.get_z() - second_vec.cords.get_z()}};
    }

    vector_t operator+ (const vector_t &second_vec) const{
        return {{cords.get_x() + second_vec.cords.get_x(), cords.get_y() + second_vec.cords.get_y(), cords.get_z() + second_vec.cords.get_z()}};
    }

    vector_t vec_prod(const vector_t &second_vec) const
    {
        ASSERT(is_valid());
        ASSERT(second_vec.is_valid());

        point_t ret_vec{
            cords.get_y() * second_vec.cords.get_z() - cords.get_z() * second_vec.cords.get_y(),
            cords.get_z() * second_vec.cords.get_x() - cords.get_x() * second_vec.cords.get_z(),
            cords.get_x() * second_vec.cords.get_y() - cords.get_y() * second_vec.cords.get_x()
        };

        return {ret_vec};
    }

    void print() const
    {
        ASSERT(is_valid());
        std::cout << "(" << cords.get_x() << ", " << cords.get_y() << ", " << cords.get_z() << ")" << std::endl;
    }

    double get_x() const { return cords.get_x(); }
    double get_y() const { return cords.get_y(); }
    double get_z() const { return cords.get_z(); }
};


class plane_t
{
    double a = NAN, b = NAN, c = NAN, d = NAN;

    vector_t norm_vec;
    point_t  plane_pnt;

    public:
    plane_t(const vector_t &norm_vec_, const point_t &plane_pnt_) : norm_vec(norm_vec_), plane_pnt(plane_pnt_)
    {
        a = norm_vec.get_x();
        b = norm_vec.get_y();
        c = norm_vec.get_z();

        d = -1 * (a * plane_pnt.get_x() + b * plane_pnt.get_y() + c * plane_pnt.get_z());
    }

    
};


class triangle_t
{
    point_t  A, B, C;
    vector_t norm_vec{(vector_t{B} - vector_t{A}).vec_prod(vector_t{C} - vector_t{A})};

    public:
    triangle_t(const point_t &A_, const point_t &B_, const point_t &C_) : A(A_), B(B_), C(C_) {}

    bool is_valid() const { return ( (A != B) && (A != C) && (B != C) ); }

    void print() const
    {
        std::cout << "\ntriangle:" << std::endl;
        std::cout << "A = ";
        A.print();
        std::cout << "B = ";
        B.print();
        std::cout << "C = ";
        C.print();
        std::cout << "norm = ";
        norm_vec.print();
    }

    bool intersects(const triangle_t &second_triag) const
    {
        ASSERT(is_valid());
        ASSERT(second_triag.is_valid());

        plane_t plane1{norm_vec, A};
        plane_t plane2{second_triag.norm_vec, second_triag.A};
    }

};

}