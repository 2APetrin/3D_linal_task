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
        double sub_det = (line2.line_pnt_.get_y() - line_pnt_.get_y()) * line2.p1_ -
                         (line2.line_pnt_.get_x() - line_pnt_.get_x()) * line2.p2_;

        double t0 = (sub_det / main_det);

        return {line_pnt_.get_x() + t0 * p1_,
                line_pnt_.get_y() + t0 * p2_,
                line_pnt_.get_z() + t0 * p3_};
    }

    main_det = p3_ * line2.p1_ - p1_ * line2.p3_;
    if (!is_equal(main_det, 0))
    {
        double sub_det = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * line2.p1_ -
                         (line2.line_pnt_.get_x() - line_pnt_.get_x()) * line2.p3_;

        double t0 = (sub_det / main_det);

        return {line_pnt_.get_x() + t0 * p1_,
                line_pnt_.get_y() + t0 * p2_,
                line_pnt_.get_z() + t0 * p3_};
    }

    main_det = p3_ * line2.p2_ - p2_ * line2.p3_;

    double sub_det = (line2.line_pnt_.get_z() - line_pnt_.get_z()) * line2.p2_ -
                     (line2.line_pnt_.get_y() - line_pnt_.get_y()) * line2.p3_;

    double t0 = (sub_det / main_det);

    return {line_pnt_.get_x() + t0 * p1_,
            line_pnt_.get_y() + t0 * p2_,
            line_pnt_.get_z() + t0 * p3_};
}

vector_t line_t::get_dir_vec() const { return dir_vec_; }
