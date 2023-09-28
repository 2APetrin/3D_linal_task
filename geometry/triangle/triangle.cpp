#include "triangle.hpp"
#include "../../include/custom_assert.hpp"
#include "../segment/segment.hpp"
#include "../point/point.hpp"
#include <iostream>

using namespace geometry;


triangle_t::triangle_t(const point_t &A, const point_t &B, const point_t &C) : A_(A), B_(B), C_(C) {}

bool triangle_t::is_valid() const { return ( (A_ != B_) && (A_ != C_) && (B_ != C_) ); }

void triangle_t::print() const
{
    std::cout << "\ntriangle:" << std::endl;
    std::cout << "A = ";
    A_.print();
    std::cout << "B = ";
    B_.print();
    std::cout << "C = ";
    C_.print();
    std::cout << "norm = ";
    norm_vec_.print();
}

bool triangle_t::intersects(const triangle_t &triag2) const
{
    ASSERT(is_valid());
    ASSERT(triag2.is_valid());

    mutual_pos plane_pos_type = plane_.get_mutual_pos_type(triag2.plane_, A_);

    std::cout << "plane pos type = " << (int)plane_pos_type << std::endl << std::endl;

    if (plane_pos_type == INTERSECT) return check_triags_in_intersect_planes(triag2);
    if (plane_pos_type == EQUAL)     return check_triags_in_same_plane(triag2);

    return false;
}

bool triangle_t::check_triag_intersect_plane(const triangle_t &triag2) const
{
    double res1 = triag2.plane_.calc_point(A_);
    double res2 = triag2.plane_.calc_point(B_);
    double res3 = triag2.plane_.calc_point(C_);
    if ((res1 > 0 && res2 > 0 && res3 > 0) ||
        (res1 < 0 && res2 < 0 && res3 < 0)) return false;

    res1 = plane_.calc_point(triag2.A_);
    res2 = plane_.calc_point(triag2.B_);
    res3 = plane_.calc_point(triag2.C_);
    if ((res1 > 0 && res2 > 0 && res3 > 0) ||
        (res1 < 0 && res2 < 0 && res3 < 0)) return false;

    return true;
}

bool triangle_t::check_triags_in_intersect_planes(const triangle_t &triag2) const
{
    ASSERT(is_valid());
    ASSERT(triag2.is_valid());

    if (!check_triag_intersect_plane(triag2))
    {
        std::cout << "check_triag_intersect_plane worked" << std::endl;
        return false;
    }

    line_t inter_line{plane_.get_intersection(triag2.plane_)};
    inter_line.print();

    segment_t seg1{get_triag_intersection(inter_line)},
              seg2{triag2.get_triag_intersection(inter_line)};

    return seg1.contains_inter_seg(seg2);
}


segment_t triangle_t::get_triag_intersection(const line_t &line) const
{
    ASSERT(is_valid());
    ASSERT(line.is_valid());

    std::cout << "\nintersection points:\n";

    int valid_cnt = 0;
    point_t p1{AB_.intersect_line(line)};
    if (p1.is_valid()) { p1.print(); valid_cnt++; }
    point_t p2{BC_.intersect_line(line)};
    if (p2.is_valid()) { p2.print(); valid_cnt++; }
    point_t p3{CA_.intersect_line(line)};
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

bool triangle_t::check_triags_in_same_plane(const triangle_t &triag2) const
{
    bool cond1 = triag2.is_in_triag(A_) ||
                 triag2.is_in_triag(B_) ||
                 triag2.is_in_triag(C_);
    if (cond1) return true;

    return AB_.intersects_seg(triag2.AB_) ||
           AB_.intersects_seg(triag2.BC_) ||
           AB_.intersects_seg(triag2.CA_) ||
           BC_.intersects_seg(triag2.AB_) ||
           BC_.intersects_seg(triag2.BC_) ||
           BC_.intersects_seg(triag2.CA_) ||
           CA_.intersects_seg(triag2.AB_) ||
           CA_.intersects_seg(triag2.BC_) ||
           CA_.intersects_seg(triag2.CA_);
}

bool triangle_t::is_in_triag(const point_t &pnt) const
{
    is_valid();
    pnt.is_valid();

    double min_x = triple_min(A_.get_x(), B_.get_x(), C_.get_x());
    double max_x = triple_max(A_.get_x(), B_.get_x(), C_.get_x());

    double min_y = triple_min(A_.get_y(), B_.get_y(), C_.get_y());
    double max_y = triple_max(A_.get_y(), B_.get_y(), C_.get_y());

    double min_z = triple_min(A_.get_z(), B_.get_z(), C_.get_z());
    double max_z = triple_max(A_.get_z(), B_.get_z(), C_.get_z());

    return gr_or_eq(pnt.get_x(), min_x) && ls_or_eq(pnt.get_x(), max_x) &&
           gr_or_eq(pnt.get_y(), min_y) && ls_or_eq(pnt.get_y(), max_y) &&
           gr_or_eq(pnt.get_z(), min_z) && ls_or_eq(pnt.get_z(), max_z);
}