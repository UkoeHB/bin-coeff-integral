# README

Binomial coefficient (`n_choose_k<T>()`) for C++ integral types (built-in and `boost::multiprecision`).

Method:
1. `n choose k = n! / (k! * (n - k)!)`
1. Factor numerator into large numbers that barely fit in `T::max()`.
1. Count the appearances of each of the denominator's prime factors.
1. Reduce the numerator terms using the denominator's prime factors.
1. When all numerator terms have been reduced as much as possible, multiply them together into the final result.

**Note**: Values `n` and `k` are pre-screened for known numerical limit failures. Doing so greatly optimizes the algorithm's worst-case performance.


## Dependencies

- `c++11`
- `boost >= 1.58`
- `cmake >= 3.13`


## Run tests

```
cmake -S . -B build
cmake --build build
./build/bin/test
```


## Notes

- Branch 'old' has some old approaches.
	- type 0: direct factorials of numerator and denominator, divide them
	- type 1: full prime factorization of numerator and denominator, cancel common primes until only numerator remains
	- type 2: direct factorial of denominator, gradually factor out the numerator into multiples of the denominator


## License

[MIT](https://opensource.org/licenses/MIT)
