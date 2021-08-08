// main

//local headers
#include "math.h"
#include "test.h"

//third party headers
#include "boost/multiprecision/cpp_int.hpp"

//standard headers
#include <cstdint>
#include <iostream>


void get_numerical_limits()
{
	// find numerical limits of binomial_coefficient_integral0 for different types
	// std::uint16_t
	std::uint16_t n1{0};
	while (binomial_coefficient_integral0<std::uint16_t>(n1, n1/2) != 0)
		++n1;
	std::cout << "binomial_coefficient_integral0<std::uint16_t>(n,k) -> max n = " << n1 - 1 << '\n';

	// std::uint32_t
	std::uint32_t n2{0};
	while (binomial_coefficient_integral0<std::uint32_t>(n2, n2/2) != 0)
		++n2;
	std::cout << "binomial_coefficient_integral0<std::uint32_t>(n,k) -> max n = " << n2 - 1 << '\n';

	// std::uint64_t
	std::uint64_t n3{0};
	while (binomial_coefficient_integral0<std::uint64_t>(n3, n3/2) != 0)
		++n3;
	std::cout << "binomial_coefficient_integral0<std::uint64_t>(n,k) -> max n = " << n3 - 1 << '\n';

	// find numerical limits of binomial_coefficient_integral1
	std::uint32_t n4{0};
	while (binomial_coefficient_integral1(n4, n4/2) != 0)
		++n4;
	std::cout << "binomial_coefficient_integral1(n,k) -> max n = " << n4 - 1 << '\n';

	// find numerical limits of binomial_coefficient_integral2 for different types
	// std::uint16_t
	std::uint16_t n5{0};
	while (binomial_coefficient_integral2<std::uint16_t>(n5, n5/2) != 0)
		++n5;
	std::cout << "binomial_coefficient_integral2<std::uint16_t>(n,k) -> max n = " << n5 - 1 << '\n';

	// std::uint32_t
	std::uint32_t n6{0};
	while (binomial_coefficient_integral2<std::uint32_t>(n6, n6/2) != 0)
		++n6;
	std::cout << "binomial_coefficient_integral2<std::uint32_t>(n,k) -> max n = " << n6 - 1 << '\n';

	// std::uint64_t
	std::uint64_t n7{0};
	while (binomial_coefficient_integral2<std::uint64_t>(n7, n7/2) != 0)
		++n7;
	std::cout << "binomial_coefficient_integral2<std::uint64_t>(n,k) -> max n = " << n7 - 1 << '\n';

	// find numerical limits of binomial_coefficient_integral3 for different types
	// std::uint16_t
	std::uint16_t n8{0};
	while (binomial_coefficient_integral3<std::uint16_t>(n8, n8/2) != 0)
		++n8;
	std::cout << "binomial_coefficient_integral3<std::uint16_t>(n,k) -> max n = " << n8 - 1 << '\n';

	// std::uint32_t
	std::uint32_t n9{0};
	while (binomial_coefficient_integral3<std::uint32_t>(n9, n9/2) != 0)
		++n9;
	std::cout << "binomial_coefficient_integral3<std::uint32_t>(n,k) -> max n = " << n9 - 1 << '\n';

	// std::uint64_t
	std::uint64_t n10{0};
	while (binomial_coefficient_integral3<std::uint64_t>(n10, n10/2) != 0)
		++n10;
	std::cout << "binomial_coefficient_integral3<std::uint64_t>(n,k) -> max n = " << n10 - 1 << '\n';

	// boost::cpp_int
	using boost::multiprecision::uint256_t;
	uint256_t limit = (uint256_t{1} << 256) - 1;
	uint256_t n11{0};
	while (binomial_coefficient_integral3_impl<uint256_t>(n11, n11/uint256_t{2}, limit, 256/8) != 0)
		++n11;
	std::cout << "binomial_coefficient_integral3<boost::multiprecision::uint256_t>(n,k,2^256) -> max n = " << n11 - 1 << '\n';
}

int main()
{
	try
	{
		run_tests();
	}
	catch (const std::exception &except)
	{
		std::cout << except.what() << '\n';
	}

	get_numerical_limits();

	return 1;
}
