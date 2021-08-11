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
#include <vector>


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
            [](const std::vector<uint16_t> &primes) -> std::uint16_t
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
    std::vector<std::uint16_t> prime_factors_300{prime_factors<std::uint16_t>(300)};

    for (const auto factor : prime_factors_300)
        EXCEPTION_ASSERT_MSG(std::find(primes_to_150.begin(), primes_to_150.end(), factor) != primes_to_150.end(), "test failed");
} TEST_END()

TEST(test_n_choose_k)
{
    std::cout << "Testing n_choose_k<T>()\n";

    EXCEPTION_ASSERT_MSG(n_choose_k<int>(-1,-1, true) == 0, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(-1,0, true) == 0, "test failed");

    EXCEPTION_ASSERT_MSG(n_choose_k<int>(0,-1, true) == 0, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(0,0, true) == 1, "test failed");

    EXCEPTION_ASSERT_MSG(n_choose_k<int>(1,0, true) == 1, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(1,1, true) == 1, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(1,2, true) == 0, "test failed");

    EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,-1, true) == 0, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,0, true) == 1, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,1, true) == 2, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(2,2, true) == 1, "test failed");

    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,1, true) == 10, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,2, true) == 45, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,3, true) == 120, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,4, true) == 210, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,5, true) == 252, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,6, true) == 210, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,7, true) == 120, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,8, true) == 45, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,9, true) == 10, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<int>(10,10, true) == 1, "test failed");

    // numerical limits
    using boost::multiprecision::cpp_int;
    cpp_int bigint_limit = (cpp_int{1} << 650) - 1;
    std::size_t bigint_size = 650/8 + (650 % 8 ? 1 : 0);
    cpp_int bigint;

    // std::uint16_t
    EXCEPTION_ASSERT_MSG(n_choose_k<std::uint16_t>(18,9, true) != 0, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<std::uint16_t>(19,9, true) == 0, "test failed");
    EXCEPTION_ASSERT_MSG(bin_coeff_get_max_k(sizeof(std::uint16_t)) == 9, "test failed");

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(18, 9, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= std::numeric_limits<std::uint16_t>::max(), "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>(19, 9, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > std::numeric_limits<std::uint16_t>::max(), "test failed");


    // std::uint32_t
    EXCEPTION_ASSERT_MSG(n_choose_k<std::uint32_t>(34,17, true) != 0, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<std::uint32_t>(35,17, true) == 0, "test failed");
    EXCEPTION_ASSERT_MSG(bin_coeff_get_max_k(sizeof(std::uint32_t)) == 17, "test failed");

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(34, 17, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= std::numeric_limits<std::uint32_t>::max(), "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>(35, 17, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > std::numeric_limits<std::uint32_t>::max(), "test failed");


    // std::uint64_t
    EXCEPTION_ASSERT_MSG(n_choose_k<std::uint64_t>(67,33, true) != 0, "test failed");
    EXCEPTION_ASSERT_MSG(n_choose_k<std::uint64_t>(68,34, true) == 0, "test failed");
    EXCEPTION_ASSERT_MSG(bin_coeff_get_max_k(sizeof(std::uint64_t)) == 33, "test failed");

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(67, 33, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= std::numeric_limits<std::uint64_t>::max(), "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>(68, 34, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > std::numeric_limits<std::uint64_t>::max(), "test failed");


    using boost::multiprecision::uint128_t;
    using boost::multiprecision::uint256_t;
    using boost::multiprecision::uint512_t;

    // uint128_t
    uint128_t a1 = n_choose_k_impl<uint128_t>(131, 65, std::numeric_limits<uint128_t>::max(), 128/8, true);
    uint128_t a2 = n_choose_k_impl<uint128_t>(132, 66, std::numeric_limits<uint128_t>::max(), 128/8, true);
    EXCEPTION_ASSERT_MSG(a1 != 0, "test failed");
    EXCEPTION_ASSERT_MSG(a2 == 0, "test failed");
    EXCEPTION_ASSERT_MSG(bin_coeff_get_max_k(128/8) == 65, "test failed");

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(131, 65, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= std::numeric_limits<uint128_t>::max(), "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>(132, 66, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > std::numeric_limits<uint128_t>::max(), "test failed");


    // uint256_t
    uint256_t b1 = n_choose_k_impl<uint256_t>(260, 130, std::numeric_limits<uint256_t>::max(), 256/8, true);
    uint256_t b2 = n_choose_k_impl<uint256_t>(261, 130, std::numeric_limits<uint256_t>::max(), 256/8, true);
    EXCEPTION_ASSERT_MSG(b1 != 0, "test failed");
    EXCEPTION_ASSERT_MSG(b2 == 0, "test failed");
    EXCEPTION_ASSERT_MSG(bin_coeff_get_max_k(256/8) == 130, "test failed");

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(260, 130, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= std::numeric_limits<uint256_t>::max(), "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>(261, 130, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > std::numeric_limits<uint256_t>::max(), "test failed");


    // uint512_t
    uint512_t c1 = n_choose_k_impl<uint512_t>(516, 258, std::numeric_limits<uint512_t>::max(), 512/8, true);
    uint512_t c2 = n_choose_k_impl<uint512_t>(517, 258, std::numeric_limits<uint512_t>::max(), 512/8, true);
    EXCEPTION_ASSERT_MSG(c1 != 0, "test failed");
    EXCEPTION_ASSERT_MSG(c2 == 0, "test failed");
    EXCEPTION_ASSERT_MSG(bin_coeff_get_max_k(512/8) == 258, "test failed");

    // valid 'n' is below max size
    bigint = n_choose_k_impl<cpp_int>(516, 258, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint <= std::numeric_limits<uint512_t>::max(), "test failed");

    // invalid 'n' is above max size
    bigint = n_choose_k_impl<cpp_int>(517, 258, bigint_limit, bigint_size, true);
    EXCEPTION_ASSERT_MSG(bigint > std::numeric_limits<uint512_t>::max(), "test failed");


    // cpp_int with 600 bits
    // test that bin_coeff_get_max_k() returns a value k such that k + 1 will fail
    cpp_int limit600 = (cpp_int{1} << 600) - 1;
    std::size_t max_expected_k = bin_coeff_get_max_k(600/8 + (600 % 8 ? 1 : 0));
    cpp_int r = n_choose_k_impl<uint512_t>((max_expected_k + 1)*2, (max_expected_k + 1), limit600, 600/8 + (600 % 8 ? 1 : 0), true);
    EXCEPTION_ASSERT_MSG(r == 0, "test failed");


    // maximum input value exceeded
    using boost::multiprecision::cpp_int;
    cpp_int limit = (cpp_int{1} << std::size_t{80000}) - 1;
    cpp_int x = n_choose_k_impl<cpp_int>(cpp_int{200000}, cpp_int{100000}, limit, std::size_t{10000}, true);
    EXCEPTION_ASSERT_MSG(x == 0, "test failed");
} TEST_END()

TEST(test_bincoeff_numerical_limits)
{
    std::cout << "Testing numerical limits of n_choose_k" << '\n';

    // built-in unsigned integral types
    // unsigned char
    unsigned char lim8 = numerical_limit_max_k<unsigned char>(sizeof(unsigned char), std::numeric_limits<unsigned char>::max());
    EXCEPTION_ASSERT_MSG(lim8 == bin_coeff_get_max_k(sizeof(unsigned char)), "test failed");

    // std::uint16_t
    std::uint16_t lim16 = numerical_limit_max_k<std::uint16_t>(sizeof(std::uint16_t), std::numeric_limits<std::uint16_t>::max());
    EXCEPTION_ASSERT_MSG(lim16 == bin_coeff_get_max_k(sizeof(std::uint16_t)), "test failed");

    // std::uint32_t
    std::uint32_t lim32 = numerical_limit_max_k<std::uint32_t>(sizeof(std::uint32_t), std::numeric_limits<std::uint32_t>::max());
    EXCEPTION_ASSERT_MSG(lim32 == bin_coeff_get_max_k(sizeof(std::uint32_t)), "test failed");

    // std::uint64_t
    std::uint64_t lim64 = numerical_limit_max_k<std::uint64_t>(sizeof(std::uint64_t), std::numeric_limits<std::uint64_t>::max());
    EXCEPTION_ASSERT_MSG(lim64 == bin_coeff_get_max_k(sizeof(std::uint64_t)), "test failed");


    // boost::multiprecision integers
    using boost::multiprecision::uint128_t;
    using boost::multiprecision::uint256_t;
    using boost::multiprecision::uint512_t;
    using boost::multiprecision::cpp_int;

    // uint128_t
    uint128_t lim128 = numerical_limit_max_k<uint128_t>(128/8, std::numeric_limits<uint128_t>::max());
    EXCEPTION_ASSERT_MSG(lim128 == bin_coeff_get_max_k(128/8), "test failed");

    // uint256_t
    uint256_t lim256 = numerical_limit_max_k<uint256_t>(256/8, std::numeric_limits<uint256_t>::max());
    EXCEPTION_ASSERT_MSG(lim256 == bin_coeff_get_max_k(256/8), "test failed");

    // uint512_t
    uint512_t lim512 = numerical_limit_max_k<uint512_t>(512/8, std::numeric_limits<uint512_t>::max());
    EXCEPTION_ASSERT_MSG(lim512 == bin_coeff_get_max_k(512/8), "test failed");

    // cpp_int: 300 bits
    cpp_int limit;
    limit = (cpp_int{1} << 300) - 1;
    cpp_int lim300 = numerical_limit_max_k<cpp_int>(300/8 + (300 % 8 ? 1 : 0), limit);
    EXCEPTION_ASSERT_MSG(lim300 < bin_coeff_get_max_k(300/8 + (300 % 8 ? 1 : 0)), "test failed");

    // cpp_int: 600 bits
    limit = (cpp_int{1} << 600) - 1;
    cpp_int lim600 = numerical_limit_max_k<cpp_int>(600/8 + (600 % 8 ? 1 : 0), limit);
    EXCEPTION_ASSERT_MSG(lim600 < bin_coeff_get_max_k(600/8 + (600 % 8 ? 1 : 0)), "test failed");
} TEST_END()

void run_tests()
{
    test_sqrt_integral();
    test_get_primes_up_to();
    test_prime_factors();
    test_n_choose_k();
    //test_bincoeff_numerical_limits();
}
