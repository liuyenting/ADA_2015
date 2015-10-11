#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota
#include <cstring>

#define MAX_N 200000

static int n;               // number of people
static long long c, p;      // c:constant, p:modulus
static long long e;         // e:exponent
static bool lut[2 * MAX_N];  // lookup table
static bool chk[2 * MAX_N];  // dirty bits

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

long long wrapped_mod(long long i, const long long& i_max)
{
	i %= i_max;
	return (i < 0) ? i+i_max : i;
}

struct queue_comparer
{
	char dummy;
	bool operator()(const long long& i, const long long& j)
	{
		if (!chk[i+j])
		{
			// ab mod n = ((a mod n)(b mod n)) mod n;
			// var > 2*p -> 2*var > p
			lut[i+j] = (2 * ((wrapped_mod(c*(i-j), p) * pow_n_mod(i+j, e, p)) % p) > p);
			chk[i+j] = true;
		}

		return lut[i+j];
	}
};

int main(void)
{
	int cases;
	std::cin >> cases;

	// pre-allocate the maximum possible size of the queue.
	std::vector<int> queue;
	queue.reserve(MAX_N);

	// setup the comparer.
	queue_comparer comparer;

	while (cases-- > 0)
	{
		//std::cerr << "cases " << (cases+1) << std::endl;

		// read the values and prep them.
		std::cin >> n >> c >> e >> p;

		// reset the lut
		std::memset(chk, false, sizeof(bool) * 2 * n);

		// resize the queue and fill with numbers
		queue.resize(n);
		std::iota(std::begin(queue), std::end(queue), 1);

		std::sort(queue.begin(), queue.end(), comparer);

		// print out the result
		for (auto i = queue.begin(); i != queue.end(); ++i)
			std::cout << *i << ' ';
		std::cout << std::endl;
	}

	return 0;
}
