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


TEST(test_sqrt_integral)
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
} TEST_END()

TEST(test_get_primes_up_to)
{
	std::cout << "Testing get_primes_up_to()\n";

	std::vector<std::uint16_t> primes_to_300{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
		37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109,
		113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197,
		199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293};

	std::vector<std::uint16_t> primes_to_200_test{get_primes_up_to(200)};
	std::vector<std::uint16_t> primes_to_300_test{get_primes_up_to(300)};
	std::vector<std::uint16_t> primes_to_400_test{get_primes_up_to(400)};

	EXCEPTION_ASSERT_MSG(primes_to_300 != primes_to_200_test, "test failed");
	EXCEPTION_ASSERT_MSG(primes_to_300 == primes_to_300_test, "test failed");
	EXCEPTION_ASSERT_MSG(primes_to_300 != primes_to_400_test, "test failed");

	EXCEPTION_ASSERT_MSG(get_primes_up_to(0).size() == 0, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(1).size() == 0, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(2).size() == 1, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(2)[0] == 2, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(3).size() == 2, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(3)[0] == 2, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(3)[1] == 3, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(4).size() == 2, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(4)[0] == 2, "test failed");
	EXCEPTION_ASSERT_MSG(get_primes_up_to(4)[1] == 3, "test failed");
} TEST_END()

TEST(test_prime_factors)
{
	std::cout << "Testing prime_factors<T>()\n";

	auto rebuild_num_f{
			[](const std::list<uint16_t> &primes) -> std::uint16_t
			{
				if (primes.size() == 0)
					return 0;

				std::uint16_t result{1};

				for (const auto prime : primes)
					result *= prime;

				return result;
			}
		};

	// factorization is complete (can reconstruct original number)
	for (std::uint16_t i{0}; i < 200; ++i)
		EXCEPTION_ASSERT_MSG(rebuild_num_f(prime_factors<std::uint16_t>(i)) == i, "test failed");

	// prime factors are actually primes
	std::vector<std::uint16_t> primes_to_150{get_primes_up_to(150)};
	std::list<std::uint16_t> prime_factors_300{prime_factors<std::uint16_t>(300)};

	for (const auto factor : prime_factors_300)
		EXCEPTION_ASSERT_MSG(std::find(primes_to_150.begin(), primes_to_150.end(), factor) != primes_to_150.end(), "test failed");
} TEST_END()

TEST(test_n_choose_k)
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
} TEST_END()

TEST(test_bincoeff_numerical_limits)
{
	std::cout << "Testing numerical limits of n_choose_k" << '\n';

	// built-in unsigned integral types
	// unsigned char
	unsigned char lim8{0};
	while (n_choose_k<unsigned char>(lim8, lim8/2, true) != 0)
		++lim8;
	EXCEPTION_ASSERT_MSG((lim8 - 1)/2 == bin_coeff_get_max_k(sizeof(unsigned char)), "test failed");

	// std::uint16_t
	std::uint16_t lim16{0};
	while (n_choose_k<std::uint16_t>(lim16, lim16/2, true) != 0)
		++lim16;
	EXCEPTION_ASSERT_MSG((lim16 - 1)/2 == bin_coeff_get_max_k(sizeof(std::uint16_t)), "test failed");

	// std::uint32_t
	std::uint32_t lim32{0};
	while (n_choose_k<std::uint32_t>(lim32, lim32/2, true) != 0)
		++lim32;
	EXCEPTION_ASSERT_MSG((lim32 - 1)/2 == bin_coeff_get_max_k(sizeof(std::uint32_t)), "test failed");

	// std::uint64_t
	std::uint64_t lim64{0};
	while (n_choose_k<std::uint64_t>(lim64, lim64/2, true) != 0)
		++lim64;
	EXCEPTION_ASSERT_MSG((lim64 - 1)/2 == bin_coeff_get_max_k(sizeof(std::uint64_t)), "test failed");


	// boost::multiprecision integers
	using boost::multiprecision::uint128_t;
	using boost::multiprecision::uint256_t;
	using boost::multiprecision::uint512_t;
	using boost::multiprecision::cpp_int;

	// uint128_t
	uint128_t lim128{0};
	while (n_choose_k_impl<uint128_t>(lim128, lim128/uint128_t{2}, std::numeric_limits<uint128_t>::max(), 128/8, true) != 0)
		++lim128;
	EXCEPTION_ASSERT_MSG((lim128 - 1)/2 == bin_coeff_get_max_k(128/8), "test failed");

	// uint256_t
	uint256_t lim256{0};
	while (n_choose_k_impl<uint256_t>(lim256, lim256/uint256_t{2}, std::numeric_limits<uint256_t>::max(), 256/8, true) != 0)
		++lim256;
	EXCEPTION_ASSERT_MSG((lim256 - 1)/2 == bin_coeff_get_max_k(256/8), "test failed");

	// uint512_t
	uint512_t lim512{0};
	while (n_choose_k_impl<uint512_t>(lim512, lim512/uint512_t{2}, std::numeric_limits<uint512_t>::max(), 512/8, true) != 0)
		++lim512;
	EXCEPTION_ASSERT_MSG((lim512 - 1)/2 == bin_coeff_get_max_k(512/8), "test failed");

	// cpp_int: 300 bits
	cpp_int limit;
	limit = (cpp_int{1} << 300) - 1;
	cpp_int lim300{0};
	while (n_choose_k_impl<cpp_int>(lim300, lim300/cpp_int{2}, limit, 300/8 + (300 % 8 ? 1 : 0), true) != 0)
		++lim300;
	EXCEPTION_ASSERT_MSG((lim300 - 1)/2 < bin_coeff_get_max_k(300/8), "test failed");

	// cpp_int: 600 bits
	limit = (cpp_int{1} << 600) - 1;
	cpp_int lim600{0};
	while (n_choose_k_impl<cpp_int>(lim600, lim600/cpp_int{2}, limit, 600/8 + (600 % 8 ? 1 : 0), true) != 0)
		++lim600;
	EXCEPTION_ASSERT_MSG((lim600 - 1)/2 < bin_coeff_get_max_k(600/8), "test failed");
} TEST_END()

void run_tests()
{
	test_sqrt_integral();
	test_get_primes_up_to();
	test_prime_factors();
	test_n_choose_k();
	test_bincoeff_numerical_limits();
}
