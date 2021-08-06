#include <cstdint>
#include <list>
#include <limits>

#include "math.h"


std::list<std::uint32_t> prime_factors(std::uint32_t n)
{
	// returns prime factors of input
	// note: does not return '1' as a prime factor

	// limited to 4 byte inputs, otherwise worst-case performance is catastrophic
	using T = std::uint32_t;

	std::list<T> result;

	// assess input
	if (n <= 1)
		return result;

	// get 2s
	while (n % 2 == 0)
	{
		result.emplace_front(2);

		n /= 2;
	}

	// iterate odd numbers
	T test{3};
	T max_test{sqrt_integral<T>(n)};

	for (T test{3}; test <= max_test; test += 2)
	{
		while (n % test == 0)
		{
			result.emplace_front(test);

			n /= test;
		}

		max_test = sqrt_integral<T>(n);
	}

	// if final n is a prime
	// example: if original n == 6, then this conditional will execute
	if (n > 1)
		result.emplace_front(n);

	return result;
}

std::uint32_t binomial_coefficient_integral_slow(std::uint32_t n, std::uint32_t k)
{
	// n choose k = n! / (k! * (n - k)!)
	// error cases (return 0)
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
		denominator_fact.merge(prime_factors(lower));

		--lower;
	}

	// roll numerator prime factors into result while cancelling factors from the denominator
	T ret_val{1};
	while (upper_a > upper_b)
	{
		std::list<T> temp(prime_factors(upper_a));
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
