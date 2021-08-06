#include <cstdint>
#include <iostream>

#include "exception_assert.h"
#include "math.h"
#include "test.h"


void test_sqrt_integral()
{
	std::cout << "Testing sqrt_integral<T>()\n";

	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(0) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(2) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(3) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(4) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(5) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(6) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(7) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(8) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<int>(9) == 3, "test failed");

	EXCEPTION_ASSERT_MSG(sqrt_integral<std::uint32_t>(10000) == 100, "test failed");
	EXCEPTION_ASSERT_MSG(sqrt_integral<std::uint32_t>(123456789) == 11111, "test failed");
}

void test_factorial()
{
	std::cout << "Testing factorial<T>()\n";

	EXCEPTION_ASSERT_MSG(factorial<int>(-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(2) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(3) == 6, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(5) == 120, "test failed");

	// another type
	EXCEPTION_ASSERT_MSG(factorial<std::size_t>(11) == 39916800, "test failed");

	// numerical limits exceeded
	EXCEPTION_ASSERT_MSG(factorial<std::uint16_t>(10) == 0, "test failed");

	// with stopping point
	EXCEPTION_ASSERT_MSG(factorial<int>(-1, -1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(0, -1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(-1, 0) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(0, 1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(0, 0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(1, 0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<int>(2, 4) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(factorial<std::size_t>(11, 5) == 
		factorial<std::size_t>(11) / factorial<std::size_t>(5), "test failed");
}

void test_binomial_coefficient_integral_fast()
{
	std::cout << "Testing binomial_coefficient_integral_fast<T>()\n";

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(-1,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(-1,0) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(0,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(2,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<int>(10,10) == 1, "test failed");

	// numerical limits exceeded
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<std::uint16_t>(12,6) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<std::uint16_t>(20,7) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_fast<std::uint16_t>(200,100) == 0, "test failed");
}

void test_binomial_coefficient_integral_slow()
{
	std::cout << "Testing binomial_coefficient_integral_slow()\n";

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(10,10) == 1, "test failed");

	// numerical limits exceeded
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral_slow(200,100) == 0, "test failed");
}

void run_tests()
{
	test_sqrt_integral();
	test_factorial();
	test_binomial_coefficient_integral_fast();
	test_binomial_coefficient_integral_slow();
}
