#ifndef GUARD_VEC_PRINT_H
#define GUARD_VEC_PRINT_H

#include <iostream>

// Print elements of a container in the range [a, b). Enclose
// output in parentheses and separate elements by commas. 
template <class It>
void iter_print(It a, It b)
{
    std::cout << "( " << *a;
    for (It i = ++a; i != b; ++i)
        std::cout << ", " << *i;
    std::cout << " )";

    return;
}

#endif