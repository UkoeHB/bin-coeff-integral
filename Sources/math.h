// math functions

#pragma once

//local headers

//third party headers

//standard headers
#include <cstdint>
#include <list>
#include <type_traits>
#include <vector>


std::vector<std::uint16_t> get_primes(std::uint16_t n);
std::uint32_t binomial_coefficient_integral_slow(std::uint32_t n, std::uint32_t k);

template <typename T>
T bin_coeff_get_max_k()
{
	// what is the largest value of (n/2) such that
	// n choose (n/2) will fit in a variable T{}?

	// note: results based on a generic online calculator
	// https://www.hackmath.net/en/calculator/n-choose-k?n=132&k=66&order=0&repeat=0
	switch (sizeof(T{}))
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
			return 262/2;
		break;
	};

	// unknown size
	return 0;
}

// thanks to: https://solarianprogrammer.com/2019/10/25/cpp-17-find-gcd-of-two-or-more-integers/
template <typename T>
T gcd(T a, T b)
{
	// Use the fact that gcd(a, b) = gcd(|a|, |b|)
	// to cover both positive and negative integers
	if (a < 0)
		a = -a;

	if (b < 0)
		b = -b;

	// Use the fact that gcd(a, b) = gcd(b, a) and gcd(a, 0) = gcd(0, a) = a.
	// Obs. this covers the case gcd(0, 0) = 0 too
	if (a == 0)
		return b;

	if (b == 0)
		return a;

	// euclidean algorithm
	T temp;

	while (a > 0)
	{
		if (a < b)
		{
			temp = a;
			a = b;
			b = temp;
		}

		a = a - b;
	}

	return b;
}

template <typename T>
T sqrt_integral(T n)
{
	// returns closest integer <= sqrt(n)
	// error: returns 0

	static_assert(std::is_integral<T>::value, "Integral type required.");

	// assess input
	if (n <= 0)
		return 0;

	// x_0 = a
	// x_(n+1) = .5*(x_n + a/x_n)
	// lim(n->inf) x_n = sqrt(a)
	// https://math.stackexchange.com/questions/217124/what-is-the-mathematical-formula-for-square-root
	T x_pre{};
	T x_post{n};
	do
	{
		x_pre = x_post;
		x_post = (x_pre + n/x_pre)/2;
	} while (x_pre > x_post);

	return x_pre;
}

template <typename T>
std::list<T> prime_factors(T n)
{
	// returns prime factors of input
	// note: does not return '1' as a prime factor
	// warning: worst-case performance if sizeof(T{}) > 4 can be catastrophic
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

template<typename T>
T factorial(T n, T s = 0)
{
	// obtains factorial: n! / s!
	// error: returns 0

	static_assert(std::is_integral<T>::value, "Integral type required.");

	if (s > n || n < 0 || s < 0)
		return 0;

	// n! / s!
	// s as in 'stop'
	T r{1};
	while (n > s)
	{ 
		if ((std::numeric_limits<T>::max() / r) < n)
			return 0;

		r *= n;
		n--;
	}

	return r;
}

template<typename T>
T binomial_coefficient_integral_fast(T n, T k)
{
	// n choose k = n! / (k! * (n - k)!)
	// error: returns 0

	static_assert(std::is_integral<T>::value, "Integral type required.");

	if (n < 0 || k < 0 || n < k)
		return 0;
	else if (n == k)
		return 1;
	else if (k >= n - k)
	{
		// (n! / k!) / (n - k)!
		T numerator{factorial<T>(n - k)};
		if (numerator == 0)
			return 0;
		else
			return factorial<T>(n, k) / numerator;
	}
	else
	{
		// (n! / (n - k)!) / k!
		T numerator{factorial<T>(k)};
		if (numerator == 0)
			return 0;
		else
			return factorial<T>(n, n - k) / numerator;
	}
}

template<typename T>
T binomial_coefficient_integral2(T n, T k)
{
	// n choose k = n! / [k! * (n - k)!]
	// error: return 0
	// - n < 0, k < 0, n < k
	// - result overflows T::max()
	static_assert(std::is_integral<T>::value, "Integral type required.");
	constexpr T max{std::numeric_limits<T>::max()};

	// input validation
	if (n < 0 || k < 0 || n < k)
		return 0;

	// special cases
	if (n == 1 || k == 0 || n == k)
		return 1;
	else if (k == 1 || k == n - 1)
		return n;

	// n choose p = (n! / (n - p)!) / p!
	// - later, will implicitly remove the larger part of denominator from numerator
	T p;
	if ((n - k) > k)
		p = k;
	else
		p = n - k;

	// denominator = p!
	// if denominator exceeds numerical limits, return error
	// note: result >= denominator ALWAYS
	T denominator{1};
	T temp{p};

	while (temp > 1)
	{ 
		if ((max / denominator) < temp)
			return 0;

		denominator *= temp;
		--temp;
	}

	// build result
	// result = (result*denominator + remainder)*[numerator terms] / denominator
	// - numerator terms = n * (n - 1) * (n - 2) * ... * (n - p + 1)
	// - iteratively multiply numerator terms onto the parens expression
	// - if remainder overflows, move it into the 'result' term
	// - if result overflows, return error
	// note: when all terms are expanded, expect remainder == 0
	T result{0};
	T remainder{1};
	T num_term{0};
	while (p > 0)
	{
		num_term = (n - p + 1);

		// apply numerator term to 'result' component
		if ((max / num_term) < result)
			return 0;

		result *= num_term;

		// apply numerator term to 'remainder' component
		if ((max / num_term) < remainder)
		{
			// remainder*num_term = x*denominator + y; y < denominator
			// note: x > 0 since max >= denominator
			// note: this will succeed because num_term*remainder > max >= denominator

			T term_increment{1};
			T temp_remainder{remainder};

			// remainder*num_term -> remainder + remainder + remainder ...
			while (term_increment <= num_term - 1)
			{
				T a{temp_remainder};
				T b{remainder};

				// handle overflow
				while (a + b < b)
				{
					// move part of remainder into result 'result' component
					// The subtracted expression can only overflow if denominator = 1, but this
					//   code will never execute in that case.
					// note: '+ 1' accounts for lost quantity on overflow
					if (max - ((max / denominator) + (a + b + 1) / denominator) < result)
						return 0;

					result += ((max / denominator) + (a + b + 1) / denominator);

					a = (a + b + 1) % denominator;
					b = max % denominator;
				}

				temp_remainder = a + b;

				++term_increment;
			}

			remainder = temp_remainder;
		}
		else
			remainder *= num_term;

		--p;
	}

	// expect (debugging): remainder % denominator == 0
	if (max - (remainder / denominator) < result)
		return 0;
	else
		return result + (remainder / denominator);
}

template<typename T>
T binomial_coefficient_integral3(T n, T k)
{
	// n choose k = n! / [k! * (n - k)!]
	// error: return 0
	// - n < 0, k < 0, n < k
	// - result overflows T::max()
	static_assert(std::is_integral<T>::value, "Integral type required.");
	constexpr T max{std::numeric_limits<T>::max()};

	// input validation
	if (n < 0 || k < 0 || n < k)
		return 0;

	// special cases
	if (n == 1 || k == 0 || n == k)
		return 1;
	else if (k == 1 || k == n - 1)
		return n;

	// n choose p = (n! / (n - p)!) / p!
	// - later, will implicitly remove (n - p)! from the numerator
	// - p <= n/2
	T p;
	if ((n - k) > k)
		p = k;
	else
		p = n - k;

	// upper bound: n max
	// - n choose 2 = n*(n-1)/2
	// - if [n choose 2] will overflow, then n is definitely too big
	// - limited this way for performance reasons
	if (n % 2 && (n / 2) * (n - 1) < (n / 2))
		return 0;
	else if (n * ((n - 1)/2) < n)
		return 0;

	// upper bound: p max
	// - lookup table (experimental results from testing cases [n choose n/2] <= T::max())
	// - limited this way for performance reasons
	if (p > bin_coeff_get_max_k<T>())
		return 0;

	// save denominator as set of prime factor counts
	// - purpose: guarding against integer overflow in the denominator

	// determine all primes needed
	std::vector<std::uint16_t> primes = get_primes(p);

	// collect prime factor counts for each term in numerator
	std::vector<T> denom_prime_factor_counts;
	denom_prime_factor_counts.resize(primes.size());

	T p_temp{p};

	while (p_temp > 0)
	{
		std::list<T> factors = prime_factors<T>(p_temp);

		for (const auto factor : factors)
		{
			for (std::size_t i{0}; i < primes.size(); ++i)
			{
				if (factor == primes[i])
					++denom_prime_factor_counts[i];
			}
		}

		--p_temp;
	}

	// save numerator as tuple of max-size factors: num! = num1*num2*...
	std::vector<T> num_factors;
	num_factors.reserve(15);	//heuristic

	T num_temp{1};
	T numerator_factor;

	while (p > 0)
	{
		numerator_factor = n - p + 1;

		// if factor will overflow, push it into vector
		if (max / num_temp < numerator_factor)
		{
			num_factors.push_back(num_temp);
			num_temp = 1;
		}

		num_temp *= numerator_factor;

		--p;
	}

	if (num_temp > 1)
		num_factors.push_back(num_temp);

	// build result
	T result{1};

	// iterate through numerator factors, reducing them by prime factors in denominator
	for (std::size_t i_numerator{0}; i_numerator < num_factors.size(); ++i_numerator)
	{
		for (std::size_t i_prime{0}; i_prime < denom_prime_factor_counts.size(); ++i_prime)
		{
			if (num_factors[i_numerator] == 0)
				break;

			while (true)
			{
				if (denom_prime_factor_counts[i_prime] == 0)
					break;

				if (num_factors[i_numerator] == 1)
					break;

				// if the prime factor divides perfectly, update numerator factor and prime counter
				if (num_factors[i_numerator] % primes[i_prime] == 0)
				{
					num_factors[i_numerator] /= primes[i_prime];
					--denom_prime_factor_counts[i_prime];
				}
				else
					break;
			}
		}

		// update result with fully reduced numerator factor (composed of only primes not present in prime counters)
		if (max / num_factors[i_numerator] < result)
			return 0;
		else
			result *= num_factors[i_numerator];
	}

	return result;
}
