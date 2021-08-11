// tests

#pragma once

//local headers
#include "math.h"

//third party headers
#include "boost/multiprecision/cpp_int.hpp"

//standard headers
#include <iostream>


template<typename T>
T numerical_limit_max_k(std::size_t size, T max)
{
    using boost::multiprecision::cpp_int;
    cpp_int bigint_limit = (cpp_int{1} << 1000) - 1;
    std::size_t bigint_size = 1000/8 + (1000 % 8 ? 1 : 0);
    cpp_int bigint;

    // heuristic to reduce test times
    T n{static_cast<T>(bin_coeff_get_max_k(size)*2 - 1)};

    bool initial_result = n_choose_k_impl<T>(n, n/T{2}, max, size, true) != 0;

    while ((n_choose_k_impl<T>(n, n/T{2}, max, size, true) != 0) == initial_result)
    {
        if (initial_result)
            ++n;
        else
            --n;
    }

    // if n was incremented, then the loop exits when n has failed
    if (initial_result)
        --n;

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(n, n/cpp_int{2}, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= max, "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>((n + 1), (n + 1)/cpp_int{2}, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > max, "test failed");

    return n/2;
}

void run_tests();



#define TEST(name)  \
void name()         \
{                   \
try                 \

#define TEST_END()  \
catch (const std::exception &except)        \
{                                           \
    std::cout << except.what() << '\n';     \
}                                           \
}                                           \
