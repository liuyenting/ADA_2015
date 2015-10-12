#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota
#include <cstring>

#define MAX_N 200000

static int n, n2;                 // number of people
static long long c, p;            // c:constant, p:modulus
static long long e;               // e:exponent
static long long lut[2 * MAX_N];  // lookup table for pow_n_mod

long long pow_n_mod(long long base,
                    long long exponent,
                    const int& modulus)
{
	long long product = 1;

	for (; exponent > 0; exponent >>= 1)
	{
		if (exponent & 0x01)
		{
			product *= base;
			product %= modulus;
		}

		// square the base
		base *= base;
		base %= modulus;
	}

	return product;
}

inline long long wrapped_mod(long long i, const long long& i_max)
{
	return (i % i_max + i_max) % i_max;
}

bool comparer(const long long& i, const long long& j)
{
	if (lut[i+j-1] == -1)
	{
		// ab mod n = ((a mod n)(b mod n)) mod n;
		// var > 2*p -> 2*var > p
		lut[i+j-1] = pow_n_mod(i+j, e, p);
	}

	return (2 * ((wrapped_mod(c*(i-j), p) * lut[i+j-1]) % p) > p);
}

int main(void)
{
	int cases;
	std::cin >> cases;

	// pre-allocate the maximum possible size of the queue.
	std::vector<int> queue;
	queue.reserve(MAX_N);

	while (cases-- > 0)
	{
		// read the values and prep them.
		std::cin >> n >> c >> e >> p;
		n2 = n * 2;

		// get the iterator
		auto end_it = queue.begin();
		std::advance(end_it, n);

		// reset the lut
		std::memset(lut, -1, sizeof(long long) * 2 * n);

		// fill with ids
		std::iota(queue.begin(), end_it, 1);

		std::sort(queue.begin(), end_it, comparer);

		// print out the result
		for (auto i = queue.begin(); i != end_it; ++i)
			std::cout << *i << ' ';
		std::cout << std::endl;
	}

	return 0;
}
