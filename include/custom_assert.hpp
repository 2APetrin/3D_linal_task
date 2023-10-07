#pragma once

#include <iostream>

#define ASSERT(cond)                      \
if (!(cond))                               \
{                                           \
    std::cout << "\nError in " << #cond      \
    << " in line "     << __LINE__            \
    << " in function " << __PRETTY_FUNCTION__  \
    << " in file "     << __FILE__ << "\n\n";   \
    abort();                                     \
}
