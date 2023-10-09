#include "custom_assert.hpp"
#include "triangle.hpp"
#include "point.hpp"
#include <iostream>

using namespace geometry;


triangle_t::triangle_t(const point_t &A, const point_t &B, const point_t &C) : A_(A), B_(B), C_(C) {}


bool triangle_t::is_valid() const
{
    return (A_.is_valid() && B_.is_valid() && C_.is_valid()) &&
           ((A_ != B_) && (A_ != C_) && (B_ != C_));
}


void triangle_t::print() const
{
    std::cout << "\ntriangle:" << std::endl;
    std::cout << "A = ";
    A_.print();
    std::cout << "B = ";
    B_.print();
    std::cout << "C = ";
    C_.print();
}


plane_t triangle_t::get_plane() const
{
    ASSERT(is_valid());

    vector_t AB = vector_t{B_} - vector_t{A_};
    vector_t AC = vector_t{C_} - vector_t{A_};

    return {AB.vec_product(AC).normalized(), A_};
}


bool triangle_t::intersects(const triangle_t &triag2) const
{
    ASSERT(is_valid());
    ASSERT(triag2.is_valid());

    double distance_squared_x9 = (triag2.get_center_vec_x3() - get_center_vec_x3()).get_squared_len();
    double bounding_sphere_radius_squared = get_bounding_sphere_radius();

    if (distance_squared_x9 > 9 * bounding_sphere_radius_squared)
        return false;

    plane_t pln1 = get_plane();
    plane_t pln2 = triag2.get_plane();
    mutual_pos plane_pos_type = pln1.get_mutual_pos_type(pln2, A_);

    switch(plane_pos_type)
    {
        case EQUAL:     return check_triags_in_same_plane(triag2);
        case INTERSECT: return check_triags_in_intersect_planes(triag2, pln1, pln2);
        case PARALLEL:  return false;
        default:        return false;
    }

    return false;
}


double triangle_t::get_bounding_sphere_radius() const
{
    ASSERT(is_valid());

    double len_AB = (vector_t{B_} - vector_t{A_}).get_squared_len();
    double len_AC = (vector_t{C_} - vector_t{A_}).get_squared_len();

    return bound_coeff * 2 * (len_AB + len_AC); // неравенство о среднем
}


vector_t triangle_t::get_center_vec_x3() const
{
    return vector_t{(A_.get_x() + B_.get_x() + C_.get_x()),
                    (A_.get_y() + B_.get_y() + C_.get_y()),
                    (A_.get_z() + B_.get_z() + C_.get_z())};
}


bool triangle_t::check_triags_in_intersect_planes(const triangle_t &triag2, const plane_t &pln1, const plane_t &pln2) const
{
    ASSERT(is_valid());
    ASSERT(triag2.is_valid());

    if (!check_triag_intersect_plane(triag2, pln1, pln2)) return false;

    line_t inter_line{pln1.get_intersection(pln2)};

    segment_t seg1{get_triag_intersection(inter_line)},
              seg2{triag2.get_triag_intersection(inter_line)};

    return seg1.contains_inter_seg(seg2);
}


bool triangle_t::check_triag_intersect_plane(const triangle_t &triag2, const plane_t &pln1, const plane_t &pln2) const
{
    double res1 = pln2.calc_point(A_);
    double res2 = pln2.calc_point(B_);
    double res3 = pln2.calc_point(C_);
    if ((res1 > 0 && res2 > 0 && res3 > 0) ||
        (res1 < 0 && res2 < 0 && res3 < 0)) return false;

    res1 = pln1.calc_point(triag2.A_);
    res2 = pln1.calc_point(triag2.B_);
    res3 = pln1.calc_point(triag2.C_);
    if ((res1 > 0 && res2 > 0 && res3 > 0) ||
        (res1 < 0 && res2 < 0 && res3 < 0)) return false;

    return true;
}


segment_t triangle_t::get_triag_intersection(const line_t &line) const
{
    ASSERT(is_valid());
    ASSERT(line.is_valid());

    segment_t AB{A_, B_};
    segment_t BC{B_, C_};
    segment_t CA{C_, A_};

    int valid_cnt = 0;

    point_t p1{AB.intersect_line(line)};
    if (p1.is_valid()) valid_cnt++;
    else if (p1.special_check())
        return AB;

    point_t p2{BC.intersect_line(line)};
    if (p2.is_valid()) valid_cnt++;
    else if (p2.special_check())
        return BC;

    point_t p3{CA.intersect_line(line)};
    if (p3.is_valid()) valid_cnt++;
    else if (p3.special_check())
        return CA;

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


bool triangle_t::is_in_triag(const point_t &pnt) const
{
    vector_t v1{(vector_t{B_} - vector_t{A_}).vec_product((vector_t{pnt} - vector_t{A_}))};
    vector_t v2{(vector_t{C_} - vector_t{B_}).vec_product((vector_t{pnt} - vector_t{B_}))};
    vector_t v3{(vector_t{A_} - vector_t{C_}).vec_product((vector_t{pnt} - vector_t{C_}))};

    vector_t resv1 = vector_t{pnt} + v1;
    vector_t resv2 = vector_t{pnt} + v2;
    vector_t resv3 = vector_t{pnt} + v3;

    plane_t plane{get_plane()};

    double res1 = plane.calc_point({resv1.get_x(), resv1.get_y(), resv1.get_z()});
    double res2 = plane.calc_point({resv2.get_x(), resv2.get_y(), resv2.get_z()});
    double res3 = plane.calc_point({resv3.get_x(), resv3.get_y(), resv3.get_z()});

    if ((res1 > 0 && res2 > 0 && res3 > 0) ||
        (res1 < 0 && res2 < 0 && res3 < 0)) return true;

    return false;
}


bool triangle_t::check_triags_in_same_plane(const triangle_t &triag2) const
{
    bool cond1 = triag2.is_in_triag(A_) ||
                 triag2.is_in_triag(B_) ||
                 triag2.is_in_triag(C_);
    if (cond1) return true;

    segment_t AB1{A_, B_},
              BC1{B_, C_},
              CA1{C_, A_},
              AB2{triag2.A_, triag2.B_},
              BC2{triag2.B_, triag2.C_},
              CA2{triag2.C_, triag2.A_};

    return AB1.intersects_seg(AB2) ||
           AB1.intersects_seg(BC2) ||
           AB1.intersects_seg(CA2) ||
           BC1.intersects_seg(AB2) ||
           BC1.intersects_seg(BC2) ||
           BC1.intersects_seg(CA2) ||
           CA1.intersects_seg(AB2) ||
           CA1.intersects_seg(BC2) ||
           CA1.intersects_seg(CA2);
}


point_t triangle_t::getA() const { return A_; }
point_t triangle_t::getB() const { return B_; }
point_t triangle_t::getC() const { return C_; }
