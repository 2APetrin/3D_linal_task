#include "segment.hpp"
#include "../../include/custom_assert.hpp"
#include "../../include/double_operations/double_operations.hpp"

using namespace geometry;


segment_t::segment_t(const point_t &first, const point_t &second) : first_(first), second_(second) {}

bool segment_t::is_valid() const { return first_.is_valid() && second_.is_valid(); }

point_t segment_t::intersect_line(const line_t &line) const
{
    if (dir_vec_.vec_product(line.get_dir_vec()) == vector_t{{0, 0, 0}})
        return {NAN, NAN, NAN};

    point_t intersection_pnt{seg_line_.get_line_intersection(line)};

    if (contains_inter_pnt(intersection_pnt)) return intersection_pnt;
    return {NAN, NAN, NAN};
}

bool segment_t::contains_inter_pnt(const point_t &pnt) const
{
    double x_min = std::min(first_.get_x(), second_.get_x()),
           x_max = std::max(first_.get_x(), second_.get_x()),
           y_min = std::min(first_.get_y(), second_.get_y()),
           y_max = std::max(first_.get_y(), second_.get_y()),
           z_min = std::min(first_.get_z(), second_.get_z()),
           z_max = std::max(first_.get_z(), second_.get_z());

    return gr_or_eq(pnt.get_x(), x_min) && ls_or_eq(pnt.get_x(), x_max) &&
           gr_or_eq(pnt.get_y(), y_min) && ls_or_eq(pnt.get_y(), y_max) &&
           gr_or_eq(pnt.get_z(), z_min) && ls_or_eq(pnt.get_z(), z_max);
}

bool segment_t::contains_inter_seg(const segment_t &seg2) const
{
    return contains_inter_pnt(seg2.first_) || contains_inter_pnt(seg2.second_) ||
           seg2.contains_inter_pnt(first_) || seg2.contains_inter_pnt(second_);
}

bool segment_t::intersects_seg(const segment_t &seg2) const
{
    point_t intersection_pnt{seg_line_.get_line_intersection(seg2.seg_line_)};
    return contains_inter_pnt(intersection_pnt) &&
      seg2.contains_inter_pnt(intersection_pnt);
}


