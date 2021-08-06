#pragma once

#include <cstdint>
#include <list>
#include <type_traits>


template <typename T>
T sqrt_integral(T n)
{
	// returns closest integer <= sqrt(n)

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

std::list<std::uint32_t> prime_factors(std::uint32_t n);
std::uint32_t binomial_coefficient_integral_slow(std::uint32_t n, std::uint32_t k);

template<typename T>
T factorial(T n, T s = 0)
{
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
	static_assert(std::is_integral<T>::value, "Integral type required.");

	// n choose k = n! / (k! * (n - k)!)
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