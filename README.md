# README

Binomial coefficient (`n_choose_k<T>()`) for C++ integral types (built-in and `boost::multiprecision`).

Method:
	- Factors numerator into large numbers that fit in `T::max()`.
	- Counts prime factors in denominator.
	- Reduces numerator terms using denominator prime factors.
	- Values `n` and `k` are pre-screened for known numerical limit failures. Doing so greatly optimizes the algorithms worst-case performance.


## Dependencies

- `c++11`
- `boost >= 1.58`
- `cmake >= 3.13`


## Run tests

```
cmake -S . -B Build
cmake --build Build
./Build/bin/exe
```


## Notes

- May not be performant for ints larger than 64 bytes (as expected).
- Branch 'old' has some old approaches.
	- type 0: direct factorials of numerator and denominator, divide them
	- type 1: full prime factorization of numerator and denominator, cancel common primes until only numerator remains
	- type 2: direct factorial of denominator, gradually factor out the numerator into multiples of the denominator


## License

[MIT](https://opensource.org/licenses/MIT)
