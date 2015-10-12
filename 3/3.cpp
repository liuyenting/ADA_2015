#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota
#include <cstring>
#include <cstdlib>

#define MAX_N 200000

static int n;                     // number of people
static long long c, p;            // c:constant, p:modulus
static long long e;               // e:exponent

static int ids[MAX_N];            // the queue
static long long lut[2 * MAX_N];  // lookup table for pow_n_mod
static int rst[MAX_N];     // result

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
	return ((i % i_max + i_max) % i_max);
}

bool comparer(const long long& i, const long long& j)
{
	if (lut[i+j-1] == -1)
		lut[i+j-1] = pow_n_mod(i+j, e, p);

	// ab mod n = ((a mod n)(b mod n)) mod n;
	// var > 2*p -> 2*var > p
	return (2 * ((wrapped_mod(c*(i-j), p) * lut[i+j-1]) % p) > p);
}

void merge (int *a, int n, int m) {
	int i, j, k;
	for (i = 0, j = m, k = 0; k < n; k++)
	{
		rst[k] = (j == n) ? a[i++]
											: (i == m) ? a[j++]
											: (comparer(a[j], a[i])) ? a[j++]
											: a[i++];
	}

	for (i = 0; i < n; i++)
	{
		a[i] = rst[i];
	}
}

void merge_sort (int *a, int n) {
	if (n < 2)
		return;
	int m = n / 2;
	merge_sort(a, m);
	merge_sort(a + m, n - m);
	merge(a, n, m);
}

int main(void)
{
	int cases;
	std::cin >> cases;

	while (cases-- > 0)
	{
		// read the values and prep them.
		std::cin >> n >> c >> e >> p;

		// reset the lut
		std::memset(lut, -1, sizeof(long long) * 2 * n);

		// fill with ids
		for (int i = 0; i < n; i++)
			ids[i] = i+1;

		merge_sort(ids, n);

		// print out the result
		//for (auto i = queue.begin(); i != end_it; ++i)
		//	std::cout << *i << ' ';
		for (int i = 0; i < n; i++)
			std::cout << ids[i] << ' ';
		std::cout << std::endl;
	}

	return 0;
}
