#pragma once

#include <cmath>
#include <iostream>
#include "custom_assert.hpp"

const double ACCURACY = 0.00001;

namespace triags {

bool equal_d(const double &num1, const double &num2) { return (std::abs(num1 - num2) < ACCURACY); }

double max_d (const double &num1, const double &num2) { return (num1 > num2) ? num1 : num2;}
double min_d (const double &num1, const double &num2) { return (num1 > num2) ? num2 : num1;}

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

        return (equal_d(x, pnt.x) && equal_d(y, pnt.y) && equal_d(z, pnt.z));
    }

    bool operator!= (const point_t &pnt) const
    {
        ASSERT(is_valid());
        ASSERT(pnt.is_valid());

        return !(equal_d(x, pnt.x) && equal_d(y, pnt.y) && equal_d(z, pnt.z));
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

    bool is_valid() const { return cords.is_valid(); }

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


class line_t
{
    vector_t dir_vec;
    point_t  line_pnt;
    double a = dir_vec.get_x();
    double b = dir_vec.get_y();
    double c = dir_vec.get_z();

    public:
    line_t(const vector_t &dir_vec_, const point_t &line_pnt_) : dir_vec(dir_vec_), line_pnt(line_pnt_) {}

    vector_t get_dir_vec() const { return dir_vec; }

    bool is_valid() const { return dir_vec.is_valid() && line_pnt.is_valid(); }

    void print() const
    {
        std::cout << std::endl << "line vec: ";
        dir_vec.print();
        std::cout << "line pnt: ";
        line_pnt.print();
    }

    point_t get_line_intersection(const line_t &line2) const
    {
        if (dir_vec.vec_prod(line2.get_dir_vec()) == vector_t{{0, 0, 0}}) return {NAN, NAN, NAN};

        double main_det = b * line2.get_a() - a * line2.get_b();
        if (!equal_d(main_det, 0))
        {
            double sub_det = (line2.line_pnt.get_y() - line_pnt.get_y()) * line2.get_a() - (line2.line_pnt.get_x() - line_pnt.get_x()) * line2.get_b();

            return {line_pnt.get_x() + (sub_det / main_det) * a,
                    line_pnt.get_y() + (sub_det / main_det) * b,
                    line_pnt.get_z() + (sub_det / main_det) * c};
        }

        main_det = c * line2.get_b() - b * line2.get_c();
        if (!equal_d(main_det, 0))
        {
            double sub_det = (line2.line_pnt.get_z() - line_pnt.get_z()) * line2.get_b() - (line2.line_pnt.get_y() - line_pnt.get_y()) * line2.get_c();

            return {line_pnt.get_x() + (sub_det / main_det) * a,
                    line_pnt.get_y() + (sub_det / main_det) * b,
                    line_pnt.get_z() + (sub_det / main_det) * c};
        }

        main_det = c * line2.get_a() - a * line2.get_c();
        double sub_det = (line2.line_pnt.get_z() - line_pnt.get_z()) * line2.get_a() - (line2.line_pnt.get_x() - line_pnt.get_x()) * line2.get_c();

        return {line_pnt.get_x() + (sub_det / main_det) * a,
                line_pnt.get_y() + (sub_det / main_det) * b,
                line_pnt.get_z() + (sub_det / main_det) * c};
    }

    double get_a() const { return a; }
    double get_b() const { return b; }
    double get_c() const { return c; }
};


class segment_t
{
    point_t first;
    point_t second;
    vector_t dir_vec{vector_t{second} - vector_t{first}};
    line_t seg_line{dir_vec, first};

    public:
    void operator= (const segment_t seg) { first = seg.first; second = seg.second;}

    segment_t(const point_t &first_, const point_t &second_) : first(first_), second(second_) {}
    segment_t(const segment_t &seg) : first(seg.get_first()), second(seg.get_second()) {}

    bool is_valid() const { return first.is_valid() && second.is_valid(); }

    point_t line_intersect(const line_t &line) const
    {
        if (dir_vec.vec_prod(line.get_dir_vec()) == vector_t{{0, 0, 0}}) return {NAN, NAN, NAN};

        point_t inter_pnt{seg_line.get_line_intersection(line)};

        if (contains_pnt(inter_pnt)) return inter_pnt;
        return {NAN, NAN, NAN};
    }

    bool contains_pnt(const point_t &pnt) const
    {
        double x_min = min_d(first.get_x(), second.get_x()),
               x_max = max_d(first.get_x(), second.get_x()),
               y_min = min_d(first.get_y(), second.get_y()),
               y_max = max_d(first.get_y(), second.get_y()),
               z_min = min_d(first.get_z(), second.get_z()),
               z_max = max_d(first.get_z(), second.get_z());

        return (pnt.get_x() > x_min || equal_d(pnt.get_x(), x_min)) &&
               (pnt.get_x() < x_max || equal_d(pnt.get_x(), x_max)) &&
               (pnt.get_y() > y_min || equal_d(pnt.get_y(), y_min)) &&
               (pnt.get_y() < y_max || equal_d(pnt.get_y(), y_max)) &&
               (pnt.get_z() > z_min || equal_d(pnt.get_z(), z_min)) &&
               (pnt.get_z() < z_max || equal_d(pnt.get_z(), z_max));
    }

    bool contains_seg(const segment_t &seg2) const
    {
        return contains_pnt(seg2.first) || contains_pnt(seg2.second) || seg2.contains_pnt(first) || seg2.contains_pnt(second);
    }

    point_t get_first()  const { return first; }
    point_t get_second() const { return second; }
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

    mutual_pos get_mutual_pos_type(const plane_t &pln, const point_t &pnt) const
    {
        vector_t res_vec = norm_vec.vec_prod(pln.norm_vec);
        vector_t null_vec{{0, 0, 0}};

        if (res_vec != null_vec) return INTERSECT;

        if (equal_d(pln.a * pnt.get_x() + pln.b * pnt.get_y() + pln.c * pnt.get_z() + pln.d, 0))
            return EQUAL;

        return PARALLEL;
    }

    line_t get_intersection(const plane_t &plane) const
    {
        double main_det = b * plane.get_c() - plane.get_b() * c;
        if (!equal_d(main_det, 0))
        {
            double sub_det1 = plane.get_d() * c - d * plane.get_c();
            double sub_det2 = plane.get_b() * d - b * plane.get_d();

            return line_t{{norm_vec.vec_prod(plane.norm_vec)}, {0, sub_det1 / main_det, sub_det2 / main_det}};
        }

        main_det = a * plane.get_c() - plane.get_a() * c;
        if (!equal_d(main_det, 0))
        {
            double sub_det1 = plane.get_d() * c - d * plane.get_c();
            double sub_det2 = plane.get_a() * d - a * plane.get_d();

            return line_t{{norm_vec.vec_prod(plane.norm_vec)}, {sub_det1 / main_det, 0, sub_det2 / main_det}};
        }

        main_det        = plane.get_b() * a - b * plane.get_a();
        double sub_det1 = plane.get_d() * b - d * plane.get_b();
        double sub_det2 = plane.get_a() * d - a * plane.get_d();

        return line_t{{norm_vec.vec_prod(plane.norm_vec)}, {sub_det1 / main_det, sub_det2 / main_det, 0}};
    }

    double calc_point(const point_t &pnt) const
    {
        std::cout << "check pnt - " << a * pnt.get_x() + b * pnt.get_y() + c * pnt.get_z() + d << std::endl;
        return a * pnt.get_x() + b * pnt.get_y() + c * pnt.get_z() + d;
    }

    double get_a() const { return a; }
    double get_b() const { return b; }
    double get_c() const { return c; }
    double get_d() const { return d; }
};


class triangle_t
{
    point_t  A, B, C;
    vector_t norm_vec{(vector_t{B} - vector_t{A}).vec_prod(vector_t{C} - vector_t{A})};
    plane_t  plane{norm_vec, A};
    segment_t AB{A, B}, BC {B, C}, CA{C, A};

    bool check_triags_in_intersect_planes(const triangle_t &triag2) const
    {
        ASSERT(is_valid());
        ASSERT(triag2.is_valid());

        if (!check_triag_intersect_plane(triag2))
        {
            std::cout << "check_triag_intersect_plane worked" << std::endl;
            return false;
        }

        line_t inter_line{plane.get_intersection(triag2.plane)};
        inter_line.print();

        segment_t seg1{get_triag_intersection(inter_line)},
                  seg2{triag2.get_triag_intersection(inter_line)};

        return seg1.contains_seg(seg2);
    }

    bool check_triags_in_same_plane(const triangle_t &triag2) const
    {
        
    }

    segment_t get_triag_intersection(const line_t &line) const
    {
        ASSERT(is_valid());
        ASSERT(line.is_valid());

        int valid_cnt = 0;
        point_t p1{AB.line_intersect(line)};
        if (p1.is_valid()) { p1.print(); valid_cnt++; }
        point_t p2{BC.line_intersect(line)};
        if (p2.is_valid()) { p2.print(); valid_cnt++; }
        point_t p3{CA.line_intersect(line)};
        if (p3.is_valid()) { p3.print(); valid_cnt++; }

        if (valid_cnt < 2) return {{NAN, NAN, NAN}, {NAN, NAN, NAN}};

        if (valid_cnt == 2)
        {
            if (!p1.is_valid()) return {p2, p3};
            if (!p2.is_valid()) return {p1, p3};
            return {p1, p2};
        }

        if (p1 == p2) return {p1, p3};
        return {p1, p2};
    }

    bool check_triag_intersect_plane(const triangle_t &triag2) const
    {
        double res1 = triag2.plane.calc_point(A);
        double res2 = triag2.plane.calc_point(B);
        double res3 = triag2.plane.calc_point(C);
        if ((res1 > 0 && res2 > 0 && res3 > 0) ||
            (res1 < 0 && res2 < 0 && res3 < 0)) return false;

        res1 = plane.calc_point(triag2.A);
        res2 = plane.calc_point(triag2.B);
        res3 = plane.calc_point(triag2.C);
        if ((res1 > 0 && res2 > 0 && res3 > 0) ||
            (res1 < 0 && res2 < 0 && res3 < 0)) return false;

        return true;
    }

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

    bool intersects(const triangle_t &triag2) const
    {
        ASSERT(is_valid());
        ASSERT(triag2.is_valid());

        mutual_pos plane_pos_type = plane.get_mutual_pos_type(triag2.plane, A);

        std::cout << "plane pos type = " << (int)plane_pos_type << std::endl << std::endl;

        if (plane_pos_type == EQUAL)     return check_triags_in_same_plane(triag2);
        if (plane_pos_type == INTERSECT) return check_triags_in_intersect_planes(triag2);

        return false;
    }
};

}