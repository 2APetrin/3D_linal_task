#pragma once

#include <iostream>

/* #define ASSERT(cond)                                                 \
if (!(cond))                                                          \
{                                                                      \
    printf("\nError in %s in line %d in function %s in file %s\n\n",    \
            #cond, __LINE__, __PRETTY_FUNCTION__, __FILE__),             \
    abort();                                                              \
} */

#define ASSERT(cond)                      \
if (!(cond))                               \
{                                           \
    std::cout << "\nError in " << #cond      \
    << " in line "     << __LINE__            \
    << " in function " << __PRETTY_FUNCTION__  \
    << " in file "     << __FILE__ << "\n\n";   \
    abort();                                     \
}
