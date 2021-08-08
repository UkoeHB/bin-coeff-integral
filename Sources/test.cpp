// tests

//local headers
#include "exception_assert.h"
#include "math.h"
#include "test.h"

//third party headers
#include "boost/multiprecision/cpp_int.hpp"

//standard headers
#include <cstdint>
#include <iostream>

void test_gcd()
{
	std::cout << "Testing gcd<T>()\n";

	EXCEPTION_ASSERT_MSG(gcd<int>(0,0) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(0,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(-1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(0,-1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(-1,-1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(2,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(1,2) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(2,2) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(-2,-2) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(4,2) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(2,4) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(-4,2) == 2, "test failed");

	EXCEPTION_ASSERT_MSG(gcd<int>(30,3) == 3, "test failed");
	EXCEPTION_ASSERT_MSG(gcd<int>(300,150) == 150, "test failed");
}

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

void test_binomial_coefficient_integral0()
{
	std::cout << "Testing binomial_coefficient_integral0<T>()\n";

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(-1,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(-1,0) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(0,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(2,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<int>(10,10) == 1, "test failed");

	// numerical limits exceeded
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<std::uint16_t>(12,6) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<std::uint16_t>(20,7) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral0<std::uint16_t>(200,100) == 0, "test failed");
}

void test_binomial_coefficient_integral1()
{
	std::cout << "Testing binomial_coefficient_integral1()\n";

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(10,10) == 1, "test failed");

	// numerical limits exceeded
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral1(200,100) == 0, "test failed");
}

void test_binomial_coefficient_integral2()
{
	std::cout << "Testing binomial_coefficient_integral2<T>()\n";

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(-1,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(-1,0) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(0,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(2,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<int>(10,10) == 1, "test failed");

	// numerical limits exceeded
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<std::uint16_t>(18,9) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral2<std::uint16_t>(200,100) == 0, "test failed");
}

void test_binomial_coefficient_integral3()
{
	std::cout << "Testing binomial_coefficient_integral3<T>()\n";

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(-1,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(-1,0) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(0,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(2,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<int>(10,10) == 1, "test failed");

	// numerical limits
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<std::uint16_t>(18,9) != 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<std::uint16_t>(19,9) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<std::uint32_t>(34,17) != 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<std::uint32_t>(35,17) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<std::uint64_t>(67,33) != 0, "test failed");
	EXCEPTION_ASSERT_MSG(binomial_coefficient_integral3<std::uint64_t>(68,34) == 0, "test failed");

	using boost::multiprecision::uint128_t;
	using boost::multiprecision::uint256_t;
	using boost::multiprecision::uint512_t;
	uint128_t a1 = binomial_coefficient_integral3_impl<uint128_t>(131, 65, std::numeric_limits<uint128_t>::max(), 128/8);
	uint128_t a2 = binomial_coefficient_integral3_impl<uint128_t>(132, 66, std::numeric_limits<uint128_t>::max(), 128/8);
	uint256_t b1 = binomial_coefficient_integral3_impl<uint256_t>(260, 130, std::numeric_limits<uint256_t>::max(), 256/8);
	uint256_t b2 = binomial_coefficient_integral3_impl<uint256_t>(261, 130, std::numeric_limits<uint256_t>::max(), 256/8);
	uint512_t c1 = binomial_coefficient_integral3_impl<uint512_t>(516, 258, std::numeric_limits<uint512_t>::max(), 512/8);
	uint512_t c2 = binomial_coefficient_integral3_impl<uint512_t>(517, 258, std::numeric_limits<uint512_t>::max(), 512/8);

	EXCEPTION_ASSERT_MSG(a1 != 0, "test failed");
	EXCEPTION_ASSERT_MSG(a2 == 0, "test failed");
	EXCEPTION_ASSERT_MSG(b1 != 0, "test failed");
	EXCEPTION_ASSERT_MSG(b2 == 0, "test failed");
	EXCEPTION_ASSERT_MSG(c1 != 0, "test failed");
	EXCEPTION_ASSERT_MSG(c2 == 0, "test failed");
}

void run_tests()
{
	test_gcd();
	test_sqrt_integral();
	test_factorial();
	test_binomial_coefficient_integral0();
	test_binomial_coefficient_integral1();
	test_binomial_coefficient_integral2();
	test_binomial_coefficient_integral3();
}
