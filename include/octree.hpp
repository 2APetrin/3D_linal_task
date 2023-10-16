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


using ans_set_t = typename std::set<size_t>;


class node_t
{
    bool isleaf_ = true;
    node_t* parent_ = nullptr;

    node_position pos_;

    std::array<plane_t, 3> planes_ = {plane_t{{1, 0, 0}, {pos_.x_, 0, 0}},
                                      plane_t{{0, 1, 0}, {0, pos_.y_, 0}},
                                      plane_t{{0, 0, 1}, {0, 0, pos_.z_}}};

    std::array<node_t*, 8>      children_;
    std::array<triag_vector, 9> triangle_vectors_;

    ans_set_t collision_ans_;

    public:

    size_t       triag_num_ = 0;
    triag_vector triags_;

    node_t(node_t* parent, node_position pos, triag_vector triags, octree_t* tree = nullptr) : parent_(parent), pos_(pos), triags_(triags)
    {
        triag_num_ = triags.size();

        if (triag_num_ < SIZE_OF_PART)
            return;

        isleaf_ = false;

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
        std::cout << "parent = " << parent_ << " this = " << this << std::endl;
        std::cout << "number of elements = " << triag_num_ << std::endl;
        std::cout << "numer of triags in border = " << triangle_vectors_[8].size() << std::endl;

        std::cout << "\n\n";
    }


    void triag_emplace(triag_id_t triag)
    {
        cube_positions triag_pos = check_triangle(triag);

        triangle_vectors_[triag_pos].push_back(triag);
    }

    cube_positions check_triangle(triag_id_t triag) const
    {
        std::array<std::array<double, 3>, 3> res;

        for (int i = 0; i < 3; i++)
        {
            res[i][0] = planes_[i].calc_point(triag.triag.getA());
            res[i][1] = planes_[i].calc_point(triag.triag.getB());
            res[i][2] = planes_[i].calc_point(triag.triag.getC());
        }

        if (all_positive(res[0][0], res[0][1], res[0][2]) && all_positive(res[1][0], res[1][1], res[1][2]) && all_positive(res[2][0], res[2][1], res[2][2])) return ZERO;
        if (all_positive(res[0][0], res[0][1], res[0][2]) && all_positive(res[1][0], res[1][1], res[1][2]) && all_negative(res[2][0], res[2][1], res[2][2])) return FRST;

        if (all_positive(res[0][0], res[0][1], res[0][2]) && all_negative(res[1][0], res[1][1], res[1][2]) && all_positive(res[2][0], res[2][1], res[2][2])) return SEC;
        if (all_positive(res[0][0], res[0][1], res[0][2]) && all_negative(res[1][0], res[1][1], res[1][2]) && all_negative(res[2][0], res[2][1], res[2][2])) return THIRD;

        if (all_negative(res[0][0], res[0][1], res[0][2]) && all_positive(res[1][0], res[1][1], res[1][2]) && all_positive(res[2][0], res[2][1], res[2][2])) return FOUR;
        if (all_negative(res[0][0], res[0][1], res[0][2]) && all_positive(res[1][0], res[1][1], res[1][2]) && all_negative(res[2][0], res[2][1], res[2][2])) return FIFTH;

        if (all_negative(res[0][0], res[0][1], res[0][2]) && all_negative(res[1][0], res[1][1], res[1][2]) && all_positive(res[2][0], res[2][1], res[2][2])) return SIXTH;
        if (all_negative(res[0][0], res[0][1], res[0][2]) && all_negative(res[1][0], res[1][1], res[1][2]) && all_negative(res[2][0], res[2][1], res[2][2])) return SEVENTH;

        return BORDER;
    }


    void get_collisions(std::vector<bool> &answer)
    {
        if (isleaf_)
        {
            for (auto it = triags_.begin(), ite = triags_.end(); it != ite; ++it)
            {
                for (auto jt = std::next(it), jte = triags_.end(); jt != jte; jt++)
                {
                    if (it->triag.intersects(jt->triag))
                    {
                        answer[it->id] = true;
                        answer[jt->id] = true;

                        //std::cout << it->id << "-" << jt->id << std::endl;
                    }
                }
            }
            return;
        }

        for (int i = 0; i < 8; i++)
            children_[i]->get_collisions(answer);

        for (auto it = triangle_vectors_[8].begin(); it != triangle_vectors_[8].end(); it++)
        {
            for (auto jt = triags_.begin(); jt != triags_.end(); jt++)
            {
                if (it->id == jt->id) continue;
                if (it->triag.intersects(jt->triag))
                {
                    answer[it->id] = true;
                    answer[jt->id] = true;

                    //std::cout << it->id << "-" << jt->id << std::endl;
                }
            }
        }
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
                                     (min_max.x_max - min_max.x_min)/2, (min_max.y_max - min_max.y_min)/2, (min_max.z_max - min_max.z_min)/2}, all_triags_, this};
    }

    ~octree_t()
    {
        delete root_;
    }

    void print()
    {
        root_->print();
    }

    void get_collisions(std::vector<bool> &answer)
    {
        root_->get_collisions(answer);
    }
};

}
