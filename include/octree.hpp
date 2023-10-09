#pragma once
#include "plane.hpp"
#include "triangle.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <array>
#include <set>

using namespace geometry;

namespace octrees{


const size_t SIZE_OF_PART = 1000;


struct triag_id_t
{
    triangle_t triag;
    size_t     id;
};

using triag_vector = std::vector<triag_id_t>;


struct node_position
{
    double x_, y_, z_;
    double x_rad_, y_rad_, z_rad_;

    node_position(double x, double y, double z, double x_rad, double y_rad, double z_rad) :
    x_(x), y_(y), z_(z), x_rad_(x_rad), y_rad_(y_rad), z_rad_(z_rad) {}
};


class octree_t;

enum cube_positions
{
    ZERO    = 0,
    FRST    = 1,
    SEC     = 2,
    THIRD   = 3,
    FOUR    = 4,
    FIFTH   = 5,
    SIXTH   = 6,
    SEVENTH = 7,
    BORDER  = 8
};

struct max_min_crds_t
{
    double x_min = std::numeric_limits<double>::infinity();
    double x_max = -x_min;

    double y_min = std::numeric_limits<double>::infinity();
    double y_max = -y_min;

    double z_min = std::numeric_limits<double>::infinity();
    double z_max = -z_min;

    void update(double x, double y, double z) {
        if (x < x_min) x_min = x;
        if (x > x_max) x_max = x;
        if (y < y_min) y_min = y;
        if (y > y_max) y_max = y;
        if (z < z_min) z_min = z;
        if (z > z_max) z_max = z;
    }
};

class node_t
{
    bool isleaf_ = true;
    node_t* parent_ = nullptr;

    node_position pos_;

    std::array<plane_t, 3> planes_ = {plane_t{{1, 0, 0}, {pos_.x_, 0, 0}},
                                      plane_t{{0, 1, 0}, {0, pos_.y_, 0}},
                                      plane_t{{0, 0, 1}, {0, 0, pos_.z_}}};

    std::array<node_t*, 8>      children_;
    std::array<triag_vector, 8> triangle_vectors_;
    octree_t* tree_ = nullptr;

    public:

    size_t       triag_num_ = 0;
    triag_vector triags_;

    node_t(node_t* parent = nullptr, node_position pos, triag_vector triags) : parent_(parent), pos_(pos), triags_(triags)
    {
        triag_num_ = triags.size();
        std::cout << "shitty size method - " << triag_num_;
        if (triag_num_ > SIZE_OF_PART) return;

        if (parent) tree_ = parent->tree_;

        double next_xrad = pos_.x_rad_ / 2;
        double next_yrad = pos_.y_rad_ / 2;
        double next_zrad = pos_.z_rad_ / 2;

        for (auto it = triags_.begin(); it != triags_.end(); it++)
        {
            triag_emplace(*it);
        }

        children_[0] = new node_t{this, node_position{pos_.x_ + pos_.x_rad_/2, pos_.y_ + pos_.y_rad_/2, pos_.z_ + pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[0]};
        children_[1] = new node_t{this, node_position{pos_.x_ + pos_.x_rad_/2, pos_.y_ + pos_.y_rad_/2, pos_.z_ - pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[1]};
        children_[2] = new node_t{this, node_position{pos_.x_ + pos_.x_rad_/2, pos_.y_ - pos_.y_rad_/2, pos_.z_ + pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[2]};
        children_[3] = new node_t{this, node_position{pos_.x_ + pos_.x_rad_/2, pos_.y_ - pos_.y_rad_/2, pos_.z_ - pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[3]};

        children_[4] = new node_t{this, node_position{pos_.x_ - pos_.x_rad_/2, pos_.y_ + pos_.y_rad_/2, pos_.z_ + pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[4]};
        children_[5] = new node_t{this, node_position{pos_.x_ - pos_.x_rad_/2, pos_.y_ + pos_.y_rad_/2, pos_.z_ - pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[5]};
        children_[6] = new node_t{this, node_position{pos_.x_ - pos_.x_rad_/2, pos_.y_ - pos_.y_rad_/2, pos_.z_ + pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[6]};
        children_[7] = new node_t{this, node_position{pos_.x_ - pos_.x_rad_/2, pos_.y_ - pos_.y_rad_/2, pos_.z_ - pos_.z_rad_/2, next_xrad, next_yrad, next_zrad}, triangle_vectors_[7]};

        isleaf_ = false;
    }

    ~node_t()
    {
        if (!isleaf_)
        {
            for (int i = 0; i < 8; i++)
                delete children_[i];
        }
    }

    void print() const
    {
        std::cout << "isleaf = " << isleaf_ << std::endl;
        std::cout << "parent = " << parent_ << "this = " << this << std::endl;
    }


    void triag_emplace(triag_id_t triag)
    {
        cube_positions triag_pos = check_triangle(triag);

        if (triag_pos == BORDER)
        {
            tree_->border_triags_.insert(triag);
            return;
        }

        triangle_vectors_[triag_pos].push_back(triag);
    }

    cube_positions check_triangle(triag_id_t triag) const
    {
        double res01 = planes_[0].calc_point(triag.triag.getA());
        double res02 = planes_[0].calc_point(triag.triag.getB());
        double res03 = planes_[0].calc_point(triag.triag.getC());

        double res11 = planes_[1].calc_point(triag.triag.getA());
        double res12 = planes_[1].calc_point(triag.triag.getB());
        double res13 = planes_[1].calc_point(triag.triag.getC());

        double res21 = planes_[2].calc_point(triag.triag.getA());
        double res22 = planes_[2].calc_point(triag.triag.getB());
        double res23 = planes_[2].calc_point(triag.triag.getC());

        if (all_positive(res01, res02, res03), all_positive(res11, res12, res13), all_positive(res21, res22, res23)) return ZERO;
        if (all_positive(res01, res02, res03), all_positive(res11, res12, res13), all_negative(res21, res22, res23)) return FRST;

        if (all_positive(res01, res02, res03), all_negative(res11, res12, res13), all_positive(res21, res22, res23)) return SEC;
        if (all_positive(res01, res02, res03), all_negative(res11, res12, res13), all_negative(res21, res22, res23)) return THIRD;

        if (all_negative(res01, res02, res03), all_positive(res11, res12, res13), all_positive(res21, res22, res23)) return FOUR;
        if (all_negative(res01, res02, res03), all_positive(res11, res12, res13), all_negative(res21, res22, res23)) return FIFTH;

        if (all_negative(res01, res02, res03), all_negative(res11, res12, res13), all_positive(res21, res22, res23)) return SIXTH;
        if (all_negative(res01, res02, res03), all_negative(res11, res12, res13), all_negative(res21, res22, res23)) return SEVENTH;

        return BORDER;
    }
};


class octree_t
{
    node_t* root_ = nullptr;

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

        root_ = new node_t{nullptr, {(min_max.x_max + min_max.x_min)/2, (min_max.y_max + min_max.y_min)/2, (min_max.z_max + min_max.z_min)/2,
                                    (min_max.x_max - min_max.x_min)/2, (min_max.y_max - min_max.y_min)/2, (min_max.z_max - min_max.z_min)/2}, all_triags_};
    }

    ~octree_t()
    {
        delete root_;
    }
};

}