// tests

#pragma once

//local headers
#include "math.h"

//third party headers
#include "boost/multiprecision/cpp_int.hpp"

//standard headers
#include <iostream>


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
