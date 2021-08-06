
#include <cstdint>
#include <iostream>

#include "math.h"
#include "test.h"


void get_numerical_limits()
{
	// find numerical limits of binomial_coefficient_integral_fast for different types
	// std::uint16_t
	std::uint16_t n1{0};
	while (binomial_coefficient_integral_fast<std::uint16_t>(n1, n1/2) != 0)
		++n1;
	std::cout << "binomial_coefficient_integral_fast<std::uint16_t>(n,k) -> max n = " << n1 - 1 << '\n';

	// std::uint32_t
	std::uint32_t n2{0};
	while (binomial_coefficient_integral_fast<std::uint32_t>(n2, n2/2) != 0)
		++n2;
	std::cout << "binomial_coefficient_integral_fast<std::uint32_t>(n,k) -> max n = " << n2 - 1 << '\n';

	// std::uint64_t
	std::uint64_t n3{0};
	while (binomial_coefficient_integral_fast<std::uint64_t>(n3, n3/2) != 0)
		++n3;
	std::cout << "binomial_coefficient_integral_fast<std::uint64_t>(n,k) -> max n = " << n3 - 1 << '\n';

	// find numerical limits of binomial_coefficient_integral_slow
	std::uint32_t n4{0};
	while (binomial_coefficient_integral_slow(n4, n4/2) != 0)
		++n4;
	std::cout << "binomial_coefficient_integral_slow -> max n = " << n4 - 1 << '\n';
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
