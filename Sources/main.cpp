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
	std::cout << "Numerical limits for [n choose (n/2)]:" << '\n';

	// find numerical limits of n_choose_k for different types
	// std::uint16_t
	std::uint16_t n8{0};
	while (n_choose_k<std::uint16_t>(n8, n8/2) != 0)
		++n8;
	std::cout << "n_choose_k<std::uint16_t>(n,k) -> max n = " << n8 - 1 << '\n';

	// std::uint32_t
	std::uint32_t n9{0};
	while (n_choose_k<std::uint32_t>(n9, n9/2) != 0)
		++n9;
	std::cout << "n_choose_k<std::uint32_t>(n,k) -> max n = " << n9 - 1 << '\n';

	// std::uint64_t
	std::uint64_t n10{0};
	while (n_choose_k<std::uint64_t>(n10, n10/2) != 0)
		++n10;
	std::cout << "n_choose_k<std::uint64_t>(n,k) -> max n = " << n10 - 1 << '\n';

	// boost::cpp_int
	using boost::multiprecision::uint128_t;
	uint128_t limit = (uint128_t{1} << 128) - 1;
	uint128_t n11{0};
	while (n_choose_k_impl<uint128_t>(n11, n11/uint128_t{2}, limit, 128/8) != 0)
		++n11;
	std::cout << "n_choose_k<boost::multiprecision::uint128_t>(n,k,2^128) -> max n = " << n11 - 1 << '\n';

	// boost::cpp_int
	using boost::multiprecision::uint256_t;
	uint256_t limit2 = (uint256_t{1} << 256) - 1;
	uint256_t n12{0};
	while (n_choose_k_impl<uint256_t>(n12, n12/uint256_t{2}, limit2, 256/8) != 0)
		++n12;
	std::cout << "n_choose_k<boost::multiprecision::uint256_t>(n,k,2^256) -> max n = " << n12 - 1 << '\n';

	// boost::cpp_int
	using boost::multiprecision::uint512_t;
	uint512_t limit3 = (uint512_t{1} << 512) - 1;
	uint512_t n13{0};
	while (n_choose_k_impl<uint512_t>(n13, n13/uint512_t{2}, limit3, 512/8) != 0)
		++n13;
	std::cout << "n_choose_k<boost::multiprecision::uint512_t>(n,k,2^512) -> max n = " << n13 - 1 << '\n';
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
