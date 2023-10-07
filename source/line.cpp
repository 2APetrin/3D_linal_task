#include "double_operations.hpp"
#include "custom_assert.hpp"
#include "line.hpp"
#include <iostream>
#include <cmath>

using namespace geometry;


line_t::line_t(const vector_t &dir_vec, const point_t &line_pnt) : dir_vec_(dir_vec), line_pnt_(line_pnt) {}


bool line_t::operator== (const line_t &line2) const
{
    return (dir_vec_.vec_product(line2.dir_vec_) == vector_t{0, 0, 0}) && check_point_belong(line2.line_pnt_);
}


bool line_t::is_valid() const { return dir_vec_.is_valid() && line_pnt_.is_valid(); }


bool line_t::check_point_belong(const point_t &pnt) const
{
    ASSERT(is_valid());
    ASSERT(pnt.is_valid());

    double p1 = dir_vec_.get_x(),
           p2 = dir_vec_.get_y(),
           p3 = dir_vec_.get_z();

    double t0 = 0;
    if (!is_equal(p1, 0))
        t0 = (pnt.get_x() - line_pnt_.get_x()) / p1;

    if (!is_equal(p2, 0))
        t0 = (pnt.get_y() - line_pnt_.get_y()) / p2;

    if (!is_equal(p3, 0))
        t0 = (pnt.get_z() - line_pnt_.get_z()) / p3;

    return is_equal(pnt.get_x() - line_pnt_.get_x(), t0 * p1) &&
           is_equal(pnt.get_y() - line_pnt_.get_y(), t0 * p2) &&
           is_equal(pnt.get_z() - line_pnt_.get_z(), t0 * p3);
}


point_t line_t::get_line_intersection_same_plane(const line_t &line2) const
{
    ASSERT(is_valid());
    ASSERT(line2.is_valid());

    if ((dir_vec_.vec_product(line2.dir_vec_) == vector_t{0, 0, 0}))
    {
        if (check_point_belong(line2.line_pnt_)) return point_t{NAN, 0, 0};
        return point_t{NAN, NAN, NAN};
    }

    double p11 = dir_vec_.get_x(),
           p12 = dir_vec_.get_y(),
           p13 = dir_vec_.get_z(),
           p21 = line2.dir_vec_.get_x(),
           p22 = line2.dir_vec_.get_y(),
           p23 = line2.dir_vec_.get_z();

    double main_det = p12 * p21 - p11 * p22;
    if (!is_equal(main_det, 0))
    {
        double sub_det = (line2.line_pnt_.get_y() - line_pnt_.get_y()) * p21 -
                         (line2.line_pnt_.get_x() - line_pnt_.get_x()) * p22;

        double t0 = (sub_det / main_det);
        return {line_pnt_.get_x() + t0 * p11,
                line_pnt_.get_y() + t0 * p12,
                line_pnt_.get_z() + t0 * p13};
    }

    main_det = p13 * p21 - p11 * p23;
    if (!is_equal(main_det, 0))
    {
        double sub_det = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * p21 -
                         (line2.line_pnt_.get_x() - line_pnt_.get_x()) * p23;

        double t0 = (sub_det / main_det);
        return {line_pnt_.get_x() + t0 * p11,
                line_pnt_.get_y() + t0 * p12,
                line_pnt_.get_z() + t0 * p13};
    }

    main_det = p13 * p22 - p12 * p23;
    double sub_det = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * p22 -
                     (line2.line_pnt_.get_y() - line_pnt_.get_y()) * p23;

    double t0 = (sub_det / main_det);
        return {line_pnt_.get_x() + t0 * p11,
                line_pnt_.get_y() + t0 * p12,
                line_pnt_.get_z() + t0 * p13};
}


vector_t line_t::get_dir_vec() const { return dir_vec_; }


void line_t::print() const
{
    std::cout << std::endl << "line vec: ";
    dir_vec_.print();
    std::cout << "line pnt: ";
    line_pnt_.print();
}
