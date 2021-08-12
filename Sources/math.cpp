// math functions

//local headers
#include "math.h"

//third party headers
#include <boost/math/special_functions/binomial.hpp>

//standard headers
#include <cmath>
#include <cstdint>


std::size_t bin_coeff_get_max_k(std::size_t size)
{
    // what is the largest value of (n/2) such that
    // n choose (n/2) will fit in an integral T{} without overflow?

    // note: results found by incrementing 'n' until failure
    switch (size)
    {
        case 1:
            return 10/2;
        case 2:
            return 18/2;
        case 4:
            return 34/2;
        case 8:
            return 67/2;
        case 16:
            return 131/2;
        case 32:
            return 260/2;
        case 64:
            return 516/2;
        case 128:
            return 1029/2;
        break;
    };

    // unknown size, approximate the answer
    return (10 * size);
}

std::vector<std::uint16_t> get_primes_up_to(const std::uint16_t n)
{
    // Eratosthenes sieve
    // get all primes in range [2, n]
    // '1' and '0' not considered primes
    std::vector<bool> sieve;
    std::vector<std::uint16_t> result;
    sieve.resize(n + 1, false);
    result.reserve(n/2);
 
    for (std::size_t i{2}; i <= n; ++i)
    {
        // If false, then it's a prime.
        if (sieve[i] == false)
        {
            // Set all multiples of 'i' to true (i.e. non-prime)
            if (i * i <= n)
            {
                for (std::size_t m{i * i}; m <= n; m += i)
                    sieve[m] = true;
            }

            // save result
            result.push_back(i);
        }
    }

    return result;
}

std::int32_t n_choose_k_bwrap(const std::uint32_t n, const std::uint32_t k)
{
    if (k > n)
        return 0;

    double fp_result = boost::math::binomial_coefficient<double>(n, k);

    if (fp_result < 0)
        return 0;

    if (fp_result > std::numeric_limits<std::int32_t>::max())
        return 0;

    return std::round(fp_result);
}

