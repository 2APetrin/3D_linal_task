#include "double_operations.hpp"
#include <cmath>

bool is_equal(const double &num1, const double &num2) { return (std::abs(num1 - num2) < ACCURACY); }

double triple_min(const double &num1, const double &num2, const double &num3)
{
    return std::min(std::min(num1, num2), num3);
}

double triple_max(const double &num1, const double &num2, const double &num3)
{
    return std::max(std::max(num1, num2), num3);
}

bool gr_or_eq(const double &num1, const double &num2)
{
    return num1 > num2 || is_equal(num1, num2);
}

bool ls_or_eq(const double &num1, const double &num2)
{
    return num1 < num2 || is_equal(num1, num2);
}


bool all_positive(const double &num1, const double &num2, const double &num3)
{
    return (num1 > 0) && (num2 > 0) && (num3 > 0);
}
bool all_negative(const double &num1, const double &num2, const double &num3)
{
    return (num1 < 0) && (num2 < 0) && (num3 < 0);
}


bool all_positive_triag_special(const double &num1, const double &num2, const double &num3)
{
    if (num1 < 0) return false;
    if (num2 < 0) return false;
    if (num3 < 0) return false;

    int zeros = 0;

    if (is_equal(num1, 0)) ++zeros;
    if (is_equal(num2, 0)) ++zeros;
    if (is_equal(num3, 0)) ++zeros;

    if (zeros > 2) return false;
    return true;
}

bool all_negative_triag_special(const double &num1, const double &num2, const double &num3)
{
    if (num1 > 0) return false;
    if (num2 > 0) return false;
    if (num3 > 0) return false;

    int zeros = 0;

    if (is_equal(num1, 0)) ++zeros;
    if (is_equal(num2, 0)) ++zeros;
    if (is_equal(num3, 0)) ++zeros;

    if (zeros > 2) return false;
    return true;
}
