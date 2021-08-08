// math functions

//local headers
#include "math.h"

//third party headers

//standard headers
#include <cstdint>
#include <list>
#include <limits>


std::size_t bin_coeff_get_max_k(std::size_t size)
{
	// what is the largest value of (n/2) such that
	// n choose (n/2) will fit in an integral T{} without overflow?

	// note: results found by incrementing n until failure
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

std::vector<std::uint16_t> get_primes(std::uint16_t n)
{
    // Eratosthenes sieve
    std::vector<bool> sieve;
    std::vector<std::uint16_t> result;
    sieve.resize(n + 1, false);
    result.reserve(n/2);
 
    for (std::size_t num{2}; num <= n; num++)
    {
        // If false, then it's a prime.
        if (sieve[num] == false)
        {
        	// Set all multiples of num to true
        	if (num * num <= n)
        	{
        		for (std::size_t multiple{num * num}; multiple <= n; multiple += num)
                	sieve[multiple] = true;
        	}

            // save result
            result.push_back(num);
        }
    }

 	return result;
}

std::uint32_t binomial_coefficient_integral1(std::uint32_t n, std::uint32_t k)
{
	// n choose k = n! / (k! * (n - k)!)
	// error: return 0
	// - n < 0, k < 0, n < k
	// - result overflows T::max()

	// note: result will overflow if n > 34

	using T = std::uint32_t;

	// assess inputs
	if (n < 0 || k < 0 || n < k)
		return 0;

	// special cases
	if (n == 1 || k == 0 || n == k)
		return 1;

	// minimize numerator
	// (upper_a! / upper_b!) / lower!
	// note: numerator >= denominator is always true
	T upper_a{n};
	T upper_b;
	T lower;
	if (k >= n - k)
	{
		upper_b = k;
		lower = n - k;
	}
	else
	{
		upper_b = n - k;
		lower = k;
	}

	// factorize denominator
	std::list<T> denominator_fact;

	while (lower > 1)
	{
		denominator_fact.merge(prime_factors<std::uint32_t>(lower));

		--lower;
	}

	// roll numerator prime factors into result while cancelling factors from the denominator
	T ret_val{1};
	while (upper_a > upper_b)
	{
		std::list<T> temp(prime_factors<std::uint32_t>(upper_a));
		auto factor_it{temp.begin()};

		while (factor_it != temp.end())
		{
			auto found_factor = std::find(denominator_fact.begin(), denominator_fact.end(), *factor_it);
			if (found_factor != denominator_fact.end())
			{
				denominator_fact.erase(found_factor);
				factor_it = temp.erase(factor_it);
			}
			else
			{
				// fails iff return value would exceed numerical limits
				if ((std::numeric_limits<T>::max() / ret_val) < *factor_it)
					return 0;

				ret_val *= *factor_it;

				++factor_it;
			}
		}

		--upper_a;
	}

	return ret_val;
}
