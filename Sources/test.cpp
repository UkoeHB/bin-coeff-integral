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

void test_n_choose_k()
{
	std::cout << "Testing n_choose_k<T>()\n";

	EXCEPTION_ASSERT_MSG(n_choose_k<int>(-1,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(-1,0) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(n_choose_k<int>(0,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(0,0) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(n_choose_k<int>(1,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(1,1) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(1,2) == 0, "test failed");

	EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,-1) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,0) == 1, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,1) == 2, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,2) == 1, "test failed");

	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,1) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,2) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,3) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,4) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,5) == 252, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,6) == 210, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,7) == 120, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,8) == 45, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,9) == 10, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,10) == 1, "test failed");

	// numerical limits
	EXCEPTION_ASSERT_MSG(n_choose_k<std::uint16_t>(18,9) != 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<std::uint16_t>(19,9) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<std::uint32_t>(34,17) != 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<std::uint32_t>(35,17) == 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<std::uint64_t>(67,33) != 0, "test failed");
	EXCEPTION_ASSERT_MSG(n_choose_k<std::uint64_t>(68,34) == 0, "test failed");

	using boost::multiprecision::uint128_t;
	using boost::multiprecision::uint256_t;
	using boost::multiprecision::uint512_t;
	uint128_t a1 = n_choose_k_impl<uint128_t>(131, 65, std::numeric_limits<uint128_t>::max(), 128/8);
	uint128_t a2 = n_choose_k_impl<uint128_t>(132, 66, std::numeric_limits<uint128_t>::max(), 128/8);
	uint256_t b1 = n_choose_k_impl<uint256_t>(260, 130, std::numeric_limits<uint256_t>::max(), 256/8);
	uint256_t b2 = n_choose_k_impl<uint256_t>(261, 130, std::numeric_limits<uint256_t>::max(), 256/8);
	uint512_t c1 = n_choose_k_impl<uint512_t>(516, 258, std::numeric_limits<uint512_t>::max(), 512/8);
	uint512_t c2 = n_choose_k_impl<uint512_t>(517, 258, std::numeric_limits<uint512_t>::max(), 512/8);

	EXCEPTION_ASSERT_MSG(a1 != 0, "test failed");
	EXCEPTION_ASSERT_MSG(a2 == 0, "test failed");
	EXCEPTION_ASSERT_MSG(b1 != 0, "test failed");
	EXCEPTION_ASSERT_MSG(b2 == 0, "test failed");
	EXCEPTION_ASSERT_MSG(c1 != 0, "test failed");
	EXCEPTION_ASSERT_MSG(c2 == 0, "test failed");
}

void run_tests()
{
	test_sqrt_integral();
	test_n_choose_k();
}
