#include "../../include/custom_assert.hpp"
#include "plane.hpp"
#include <iostream>

using namespace geometry;


plane_t::plane_t(const vector_t &norm_vec, const point_t &plane_pnt) : norm_vec_(norm_vec), plane_pnt_(plane_pnt)
{
    a_ = norm_vec.get_x();
    b_ = norm_vec.get_y();
    c_ = norm_vec.get_z();

    d_ = -1 * (a_ * plane_pnt.get_x() + b_ * plane_pnt.get_y() + c_ * plane_pnt.get_z());
}

bool plane_t::is_valid() const { return norm_vec_.is_valid() && plane_pnt_.is_valid(); }

mutual_pos plane_t::get_mutual_pos_type(const plane_t &pln, const point_t &pnt) const
{
    ASSERT(is_valid());
    ASSERT(pln.is_valid());
    ASSERT(pnt.is_valid());

    vector_t res_vec = norm_vec_.vec_product(pln.norm_vec_);

    if (res_vec != vector_t{{0, 0, 0}}) return INTERSECT;

    if (is_equal(pln.a_ * pnt.get_x() + pln.b_ * pnt.get_y() + pln.c_ * pnt.get_z() + pln.d_, 0))
        return EQUAL;

    return PARALLEL;
}

line_t plane_t::get_intersection(const plane_t &plane) const
{
    double main_det = b_ * plane.get_c() - plane.get_b() * c_;
    if (!is_equal(main_det, 0))
    {
        double sub_det1 = plane.get_d() * c_ - d_ * plane.get_c();
        double sub_det2 = plane.get_b() * d_ - b_ * plane.get_d();

        return line_t{{norm_vec_.vec_product(plane.norm_vec_)}, {0, (sub_det1 / main_det), (sub_det2 / main_det)}};
    }

    main_det = a_ * plane.get_c() - plane.get_a() * c_;
    if (!is_equal(main_det, 0))
    {
        double sub_det1 = plane.get_d() * c_ - d_ * plane.get_c();
        double sub_det2 = plane.get_a() * d_ - a_ * plane.get_d();

        return line_t{{norm_vec_.vec_product(plane.norm_vec_)}, {(sub_det1 / main_det), 0, (sub_det2 / main_det)}};
    }

    main_det = plane.get_b() * a_ - b_ * plane.get_a();
    if(!is_equal(main_det, 0))
    {
        double sub_det1 = plane.get_d() * b_ - d_ * plane.get_b();
        double sub_det2 = plane.get_a() * d_ - a_ * plane.get_d();

        return line_t{{norm_vec_.vec_product(plane.norm_vec_)}, {(sub_det1 / main_det), (sub_det2 / main_det), 0}};
    }

    return {{{NAN, NAN, NAN}}, {NAN, NAN, NAN}};
}

double plane_t::calc_point(const point_t &pnt) const
{
    std::cout << "calc pnt - " << a_ * pnt.get_x() + b_ * pnt.get_y() + c_ * pnt.get_z() + d_ << std::endl;
    return a_ * pnt.get_x() + b_ * pnt.get_y() + c_ * pnt.get_z() + d_;
}



double plane_t::get_a() const { return a_; }
double plane_t::get_b() const { return b_; }
double plane_t::get_c() const { return c_; }
double plane_t::get_d() const { return d_; }