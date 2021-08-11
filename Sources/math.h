// math functions

#pragma once

//local headers
#include "is_multiprecision_int.h"

//third party headers

//standard headers
#include <cstdint>
#include <type_traits>
#include <vector>


std::vector<std::uint16_t> get_primes_up_to(std::uint16_t n);
std::size_t bin_coeff_get_max_k(std::size_t size);

template <typename T>
T get_mid(const T a, const T b)
{
    //returns the average of two numbers; overflow safe and works with at least all integral and floating point types
    //(a+b)/2 = (a/2) + (b/2) + ((a - 2*(a/2)) + (b - 2*(b/2)))/2
    return (a/2) + (b/2) + ((a - 2*(a/2)) + (b - 2*(b/2)))/2;
}

template <typename T>
T sqrt_integral(const T n)
{
    // returns closest integer <= sqrt(n)
    // error: returns 0
    static_assert(std::is_integral<T>::value || is_multiprecision_int<T>::value, "Integral type required.");

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
        x_post = get_mid<T>(x_pre, n/x_pre);
    } while (x_pre > x_post);

    return x_pre;
}

template <typename T>
std::vector<T> prime_factors(T n)
{
    // returns prime factors of input
    // note: does not return '1' as a prime factor unless n == 1
    // warning: worst-case performance if sizeof(T{}) > 4 can be catastrophic
    static_assert(std::is_integral<T>::value || is_multiprecision_int<T>::value, "Integral type required.");

    std::vector<T> result;

    // figure max number of prime factors
    std::size_t count{0};

    while ((T{1} << count) < n)
        count += 4;

    result.reserve(count + 1);

    // assess input
    if (n == 0)
        return result;
    else if (n == 1)
    {
        result.push_back(1);
        return result;
    }

    // get 2s
    while (n % 2 == 0)
    {
        result.push_back(2);

        n /= 2;
    }

    // iterate odd numbers
    T test{3};
    T max_test{sqrt_integral<T>(n)};

    for (T test{3}; test <= max_test; test += 2)
    {
        while (n % test == 0)
        {
            result.push_back(test);

            n /= test;
        }

        max_test = sqrt_integral<T>(n);
    }

    // if final n is a prime
    // example: if original n == 6, then this conditional will execute
    if (n > 1)
        result.push_back(n);

    return result;
}

template<typename T>
T n_choose_k_impl(const T n, const T k, const T type_max, const std::size_t type_size, const bool testing = false)
{
    // binomial coefficient: n choose k = n! / [k! * (n - k)!]
    // error: return 0
    // - n < 0, k < 0, n < k
    // - min(k, n - k) > 2^16 - 1 = 65535
    // - result > T::max()
    static_assert(std::is_integral<T>::value || is_multiprecision_int<T>::value, "Integral type required.");

    // input validation
    if (n < 0 || k < 0 || n < k)
        return 0;

    // special cases
    if (n == 1 || k == 0 || n == k)
        return 1;
    else if (k == 1 || k == n - 1)
        return n;

    // n choose p = (n! / (n - p)!) / p!
    // - later, (n - p)! will be implicitly removed from the numerator
    // - p <= n/2
    T p;
    if ((n - k) > k)
        p = k;
    else
        p = n - k;

    // upper bound: n max
    // - n choose 2 = n*(n-1)/2
    // - if [n choose 2] overflows, then [n choose p, p >= 2] will overflow
    // - limited this way for performance reasons
    if (n % 2 && (n / 2) * (n - 1) < (n / 2))
        return 0;
    else if (n * ((n - 1)/2) < n)
        return 0;

    // upper bound: p max
    // - lookup table (experimental results from testing cases [n choose n/2] <= T::max())
    // - [n choose (n/2)] is the max result in the 'n' series,
    //   so if (n'/2 = p) is too big, then [n choose p] will overflow
    // - limited this way for performance reasons
    if (!testing)
    {
        if (p > bin_coeff_get_max_k(type_size))
            return 0;
    }

    // save denominator as set of prime factor counts
    // - purpose: guarding against integer overflow in the denominator

    // determine all primes needed
    if (p > std::numeric_limits<std::uint16_t>::max())
        return 0;

    std::vector<std::uint16_t> primes = get_primes_up_to(static_cast<std::uint16_t>(p));

    // collect prime factor counts for each term in denominator
    // p! -> prime_factors(p), prime_factors(p - 1), ...
    std::vector<T> denom_prime_factor_counts;
    denom_prime_factor_counts.resize(primes.size());

    T p_temp{p};

    while (p_temp > 1)
    {
        std::vector<T> factors = prime_factors<T>(p_temp);

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

    // save numerator as tuple of max-size factors
    // n! / (n - p)! = num1*num2*...
    // note: this is where the value '(n - p)!' is implicitly removed from 'n!'
    std::vector<T> num_factors;
    num_factors.reserve(15);    //heuristic

    T num_temp{1};
    T numerator_factor;

    while (p > 0)
    {
        // n! / (n - p)! = [n - p + 1] * [n - (p-1) + 1] * ... * [n - 1 + 1]
        numerator_factor = n - p + 1;

        // if factor will overflow, push it into vector
        if (type_max / num_temp < numerator_factor)
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

    // iterate through big numerator factors, reducing them by prime factors in denominator
    for (std::size_t i_numerator{0}; i_numerator < num_factors.size(); ++i_numerator)
    {
        // note: reuse this variable from earlier
        numerator_factor = num_factors[i_numerator];

        for (std::size_t i_primes{0}; i_primes < denom_prime_factor_counts.size(); ++i_primes)
        {
            // leave if no more numerator primes can be removed
            if (numerator_factor < primes[i_primes])
                break;

            while (true)
            {
                if (denom_prime_factor_counts[i_primes] == 0)
                    break;

                // if the prime factor divides perfectly, update numerator factor and prime counter
                if (numerator_factor % primes[i_primes] == 0)
                {
                    numerator_factor /= primes[i_primes];
                    --denom_prime_factor_counts[i_primes];
                }
                else
                    break;
            }
        }

        // update result with fully reduced numerator factor (composed of only primes not present in prime counters)
        if (type_max / numerator_factor < result)
            return 0;
        else
            result *= numerator_factor;
    }

    // numerator should have no remaining prime factors
    if (testing)
    {
        for (const auto count : denom_prime_factor_counts)
        {
            if (count)
                return 0;
        }
    }

    return result;
}

template<typename T>
T n_choose_k(T n, T k, const bool testing = false)
{
    // wrapper for n_choose_k that supports built-in types
    static_assert(std::is_integral<T>::value, "Integral type required (boost::multiprecision not allowed here).");
    constexpr T type_max{std::numeric_limits<T>::max()};
    
    return n_choose_k_impl<T>(n, k, type_max, sizeof(T), testing);
}
