// tests

#pragma once

//local headers

//third party headers

//standard headers
#include <iostream>


#define TEST(name)  \
void name()		 	\
{ 					\
try 				\

#define TEST_END()  \
catch (const std::exception &except)		\
{											\
	std::cout << except.what() << '\n';		\
}											\
}											\

void run_tests();
