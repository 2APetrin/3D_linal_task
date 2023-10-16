#pragma once

const double ACCURACY = 0.00001;

bool is_equal(const double &num1, const double &num2);

double triple_min(const double &num1, const double &num2, const double &num3);
double triple_max(const double &num1, const double &num2, const double &num3);

bool gr_or_eq(const double &num1, const double &num2);
bool ls_or_eq(const double &num1, const double &num2);

bool all_positive(const double &num1, const double &num2, const double &num3);
bool all_negative(const double &num1, const double &num2, const double &num3);

bool all_positive_triag_special(const double &num1, const double &num2, const double &num3);
bool all_negative_triag_special(const double &num1, const double &num2, const double &num3);