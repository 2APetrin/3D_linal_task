#pragma once
#include "double_operations.hpp"
#include "triangle.hpp"
#include "plane.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include <list>
#include <set>

using namespace geometry;
using namespace doperations;


namespace octrees{

const size_t SIZE_OF_PART = 100;


struct triag_id_t
{
    triangle_t triag;
    size_t     id;
};


using triag_vector = std::vector<triag_id_t>;


struct cube_position
{
    double x_, y_, z_;
    double x_rad_, y_rad_, z_rad_;

    cube_position(double x, double y, double z, double x_rad, double y_rad, double z_rad) :
    x_(x), y_(y), z_(z), x_rad_(x_rad), y_rad_(y_rad), z_rad_(z_rad) {}

    void print() const
    {
        std::cout << "center   = (" << x_ << ", " << y_ << ", " << z_ << ")\n";
        std::cout << "radiuses = " << x_rad_ << ", " << y_rad_ << ", " << z_rad_ << "\n";
    }
};


enum cube_positions
{
    ZERO    = 0,
    FRST    = 1,
    SEC     = 2,
    THIRD   = 3,
    FOUR    = 4,
    FIFTH   = 5,
    SIXTH   = 6,
    SEVENTH = 7
};


struct max_min_crds_t
{
    double x_min = std::numeric_limits<double>::infinity();
    double x_max = -x_min;

    double y_min = std::numeric_limits<double>::infinity();
    double y_max = -y_min;

    double z_min = std::numeric_limits<double>::infinity();
    double z_max = -z_min;

    void update(double x, double y, double z)
    {
        if (x < x_min) x_min = x;
        if (x > x_max) x_max = x;
        if (y < y_min) y_min = y;
        if (y > y_max) y_max = y;
        if (z < z_min) z_min = z;
        if (z > z_max) z_max = z;
    }

    void print()
    {
        std::cout << "xmin = " << x_min << "\nxmax = " << x_max << "\n";
        std::cout << "ymin = " << y_min << "\nymax = " << y_max << "\n";
        std::cout << "zmin = " << z_min << "\nzmax = " << z_max << "\n";
    }
};


class octree_t;

const int child_num = 8;


bool is_point_in_cube(const point_t& pnt, const cube_position& pos)
{
    double minx = pos.x_ - pos.x_rad_,
           maxx = pos.x_ + pos.x_rad_,
           miny = pos.y_ - pos.y_rad_,
           maxy = pos.y_ + pos.y_rad_,
           minz = pos.z_ - pos.z_rad_,
           maxz = pos.z_ + pos.z_rad_;

    double px = pnt.get_x(), py = pnt.get_y(), pz = pnt.get_z();

    bool fits_x = (gr_or_eq(px, minx) && ls_or_eq(px, maxx));
    bool fits_y = (gr_or_eq(py, miny) && ls_or_eq(py, maxy));
    bool fits_z = (gr_or_eq(pz, minz) && ls_or_eq(pz, maxz));

    return fits_x && fits_y && fits_z;
}


inline bool is_in_cube(const triangle_t& triag, const cube_position& pos)
{
    return is_point_in_cube(triag.getA(), pos) ||
           is_point_in_cube(triag.getB(), pos) ||
           is_point_in_cube(triag.getC(), pos);
}


namespace detail {

class node_t
{
    node_t* parent_;

    bool isleaf_ = true;

    cube_position pos_;

    std::array<plane_t, 3> planes_ = {plane_t{{1, 0, 0}, {pos_.x_, 0, 0}},
                                      plane_t{{0, 1, 0}, {0, pos_.y_, 0}},
                                      plane_t{{0, 0, 1}, {0, 0, pos_.z_}}};

    std::array<node_t*, child_num> children_;
    std::array<triag_vector, child_num> triangle_vectors_;

    public:

    size_t       triag_num_ = 0;
    triag_vector triags_;

    node_t(node_t* parent, cube_position pos, triag_vector triags, std::list<node_t> &nodes) : parent_(parent), pos_(pos), triags_(triags)
    {
        triag_num_ = triags.size();

        if (triag_num_ < SIZE_OF_PART)
            return;

        isleaf_ = false;

        double next_xrad = pos_.x_rad_ / 2;
        double next_yrad = pos_.y_rad_ / 2;
        double next_zrad = pos_.z_rad_ / 2;

        std::vector<cube_position> children_pos;

        for (int i = 0; i < child_num; ++i)
        {
            children_pos.push_back({pos_.x_ + ((i & (1 << 0)) ? -next_xrad : next_xrad),
                                    pos_.y_ + ((i & (1 << 1)) ? -next_yrad : next_yrad),
                                    pos_.z_ + ((i & (1 << 2)) ? -next_zrad : next_zrad),
                                    next_xrad, next_yrad, next_zrad});
        }

        for (auto it = triags_.begin(), ite = triags_.end(); it != ite; ++it) triag_emplace(*it, children_pos);

        for (int i = 0; i < child_num; ++i)
        {
            nodes.push_back(node_t{this, children_pos[i], triangle_vectors_[i], nodes});
            children_[i] = &(*std::prev(nodes.end()));
        }
    }


    void print() const
    {
        std::cout << "isleaf = " << isleaf_ << std::endl;
        std::cout << "parent = " << parent_ << " this = " << this << std::endl;
        std::cout << "number of elements = " << triag_num_ << std::endl;

        std::cout << "\n\n";
    }


    void triag_emplace(triag_id_t trg, std::vector<cube_position> &child_positions)
    {
        for (int i = 0; i < 8; ++i)
            if (is_in_cube(trg.triag, child_positions[i])) triangle_vectors_[i].push_back(trg);
    }


    void get_collisions(std::vector<bool> &answer)
    {
        if (isleaf_)
        {
            for (auto it = triags_.begin(), ite = triags_.end(); it != ite; ++it)
            {
                for (auto jt = std::next(it), jte = triags_.end(); jt != jte; ++jt)
                {
                    if (it->triag.intersects(jt->triag))
                    {
                        answer[it->id] = true;
                        answer[jt->id] = true;
                    }
                }
            }
            return;
        }

        for (int i = 0; i < child_num; ++i)
            children_[i]->get_collisions(answer);
    }
};

}


class octree_t
{
    detail::node_t* root_ = nullptr;
    std::list<detail::node_t> nodes_;

    triag_vector all_triags_;

    public:

    std::set<triag_id_t> border_triags_;

    octree_t(triag_vector all_triags) : all_triags_(all_triags)
    {
        max_min_crds_t min_max{};

        for (auto it = all_triags_.begin(); it != all_triags_.end(); it++)
        {
            point_t A{it->triag.getA()};
            point_t B{it->triag.getB()};
            point_t C{it->triag.getC()};

            min_max.update(A.get_x(), A.get_y(), A.get_z());
            min_max.update(B.get_x(), B.get_y(), B.get_z());
            min_max.update(C.get_x(), C.get_y(), C.get_z());
        }

        cube_position pos{(min_max.x_max + min_max.x_min)/2, (min_max.y_max + min_max.y_min)/2, (min_max.z_max + min_max.z_min)/2,
                          (min_max.x_max - min_max.x_min)/2, (min_max.y_max - min_max.y_min)/2, (min_max.z_max - min_max.z_min)/2};

        nodes_.push_back(detail::node_t{nullptr, pos, all_triags_, nodes_});
        root_ = &(*std::prev(nodes_.end()));
    }

    void print() { root_->print(); }

    void get_collisions(std::vector<bool> &answer) { root_->get_collisions(answer); }
};

}
