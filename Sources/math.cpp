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
