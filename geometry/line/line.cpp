#include "../../include/double_operations/double_operations.hpp"
#include "line.hpp"
#include <iostream>

using namespace geometry;


line_t::line_t(const vector_t &dir_vec, const point_t &line_pnt) : dir_vec_(dir_vec), line_pnt_(line_pnt) {}

bool line_t::is_valid() const { return dir_vec_.is_valid() && line_pnt_.is_valid(); }

void line_t::print() const
{
    std::cout << std::endl << "line vec: ";
    dir_vec_.print();
    std::cout << "line pnt: ";
    line_pnt_.print();
}

point_t line_t::get_line_intersection(const line_t &line2) const
{
    if (dir_vec_.vec_product(line2.dir_vec_) == vector_t{{0, 0, 0}})
        return {NAN, NAN, NAN};

    double main_det = p2_ * line2.p1_ - p1_ * line2.p2_;
    if (!is_equal(main_det, 0))
    {
        double sub_det1 = (line2.line_pnt_.get_y() - line_pnt_.get_y()) * line2.p1_ -
                          (line2.line_pnt_.get_x() - line_pnt_.get_x()) * line2.p2_;

        double t0 = (sub_det1 / main_det);
        point_t point1 = {line_pnt_.get_x() + t0 * p1_,
                          line_pnt_.get_y() + t0 * p2_,
                          line_pnt_.get_z() + t0 * p3_};

        double sub_det2 = (line2.line_pnt_.get_y() - line_pnt_.get_y()) * p1_ -
                          (line2.line_pnt_.get_x() - line_pnt_.get_x()) * p2_;

        double s0 = (sub_det2 / main_det);
        point_t point2 = {line2.line_pnt_.get_x() + s0 * line2.p1_,
                          line2.line_pnt_.get_y() + s0 * line2.p2_,
                          line2.line_pnt_.get_z() + s0 * line2.p3_};

        if (point1 == point2) return point1;
        return {NAN, NAN, NAN};
    }

    main_det = p3_ * line2.p1_ - p1_ * line2.p3_;
    if (!is_equal(main_det, 0))
    {
        double sub_det1 = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * line2.p1_ -
                          (line2.line_pnt_.get_x() - line_pnt_.get_x()) * line2.p3_;

        double t0 = (sub_det1 / main_det);
        point_t point1 = {line_pnt_.get_x() + t0 * p1_,
                          line_pnt_.get_y() + t0 * p2_,
                          line_pnt_.get_z() + t0 * p3_};

        double sub_det2 = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * p1_ -
                          (line2.line_pnt_.get_x() - line_pnt_.get_x()) * p3_;

        double s0 = (sub_det2 / main_det);
        point_t point2 = {line2.line_pnt_.get_x() + s0 * line2.p1_,
                          line2.line_pnt_.get_y() + s0 * line2.p2_,
                          line2.line_pnt_.get_z() + s0 * line2.p3_};

        if (point1 == point2) return point1;
        return {NAN, NAN, NAN};
    }

    main_det = p3_ * line2.p2_ - p2_ * line2.p3_;

    double sub_det1 = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * line2.p2_ -
                      (line2.line_pnt_.get_y() - line_pnt_.get_y()) * line2.p3_;

    double t0 = (sub_det1 / main_det);
    point_t point1 = {line_pnt_.get_x() + t0 * p1_,
                      line_pnt_.get_y() + t0 * p2_,
                      line_pnt_.get_z() + t0 * p3_};

    double sub_det2 = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * p2_ -
                      (line2.line_pnt_.get_y() - line_pnt_.get_y()) * p3_;

    double s0 = (sub_det2 / main_det);
    point_t point2 = {line2.line_pnt_.get_x() + s0 * line2.p1_,
                      line2.line_pnt_.get_y() + s0 * line2.p2_,
                      line2.line_pnt_.get_z() + s0 * line2.p3_};

    if (point1 == point2) return point1;
    return {NAN, NAN, NAN};
}

vector_t line_t::get_dir_vec() const { return dir_vec_; }

bool line_t::check_belong_point(const point_t &pnt) const
{
    double t0 = 0;
    if (!is_equal(p1_, 0))
        t0 = (pnt.get_x() - line_pnt_.get_x()) / p1_;

    if (!is_equal(p2_, 0))
        t0 = (pnt.get_y() - line_pnt_.get_y()) / p2_;

    if (!is_equal(p3_, 0))
        t0 = (pnt.get_z() - line_pnt_.get_z()) / p3_;

    return is_equal(pnt.get_x() - line_pnt_.get_x(), t0 * p1_) &&
           is_equal(pnt.get_y() - line_pnt_.get_y(), t0 * p2_) &&
           is_equal(pnt.get_z() - line_pnt_.get_z(), t0 * p3_);
}


bool line_t::operator== (const line_t &line2) const
{
    return (dir_vec_.vec_product(line2.dir_vec_) == vector_t{{0, 0, 0}}) && check_belong_point(line2.line_pnt_);
}

