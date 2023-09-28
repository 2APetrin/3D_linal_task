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