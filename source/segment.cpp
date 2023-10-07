#include "segment.hpp"
#include "custom_assert.hpp"
#include "double_operations.hpp"

using namespace geometry;


segment_t::segment_t(const point_t &first, const point_t &second) : first_(first), second_(second) {}


bool segment_t::is_valid() const { return first_.is_valid() && second_.is_valid(); }


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


bool segment_t::intersects_seg(const segment_t &seg2) const
{
    line_t seg_line1{vector_t{second_} - vector_t{first_}, first_};
    line_t seg_line2{vector_t{seg2.second_} - vector_t{seg2.first_}, seg2.first_};

    point_t intersection_pnt{seg_line1.get_line_intersection_same_plane(seg_line2)};

    if (intersection_pnt.special_check())
    {
        if (contains_inter_seg(seg2)) return true;
        return false;
    }

    return contains_inter_pnt(intersection_pnt) &&
      seg2.contains_inter_pnt(intersection_pnt);
}


point_t segment_t::intersect_line(const line_t &line) const
{
    vector_t dir_vec = vector_t{second_} - vector_t{first_};
    line_t seg_line{dir_vec, first_};

    if (dir_vec.vec_product(line.get_dir_vec()) == vector_t{{0, 0, 0}} && !(line.check_point_belong(first_)))
        return {NAN, NAN, NAN};

    if (dir_vec.vec_product(line.get_dir_vec()) == vector_t{{0, 0, 0}} && (line.check_point_belong(first_)))
        return {NAN, 0, 0};

    point_t intersection_pnt{seg_line.get_line_intersection_same_plane(line)};

    if (contains_inter_pnt(intersection_pnt)) return intersection_pnt;
    return {NAN, NAN, NAN};
}


bool segment_t::contains_inter_seg(const segment_t &seg2) const
{
    return contains_inter_pnt(seg2.first_) || contains_inter_pnt(seg2.second_) ||
           seg2.contains_inter_pnt(first_) || seg2.contains_inter_pnt(second_);
}
