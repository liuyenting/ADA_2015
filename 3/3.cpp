#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota
#include <cstring>

#define MAX_N 200000

static int n;             // number of people
static long long c, p;          // c:constant, p:modulus
static long long e;       // e:exponent

long long pow_n_mod(long long base,
                    long long exponent,
                    const int& modulus)
{
	long long product = 1;

	while (exponent > 0)
	{
		if (exponent % 2 == 1)
		{
			product *= base;
			product %= modulus;
		}
		exponent >>= 1;

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

char lut[MAX_N][MAX_N];
void clear_lut(const int& size)
{
	memset(lut, 0, sizeof(char) * size * size);
}

struct queue_comparer
{
	bool operator()(const long long& i, const long long& j)
	{
		if (lut[i][j] == 0)
			// ab mod n = ((a mod n)(b mod n)) mod n;
			// var > 2*p -> 2*var > p
			lut[i][j] = (2 * ((wrapped_mod(c*(i-j), p) * pow_n_mod(i+j, e, p)) % p) > p) ? 2 : 1;

		return lut[i][j] == 2;
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
		std::cerr << "cases " << (cases+1) << std::endl;

		// read the values and prep them.
		//std::cin >> comparer.n >> comparer.c >> comparer.e >> comparer.p;
		std::cin >> n >> c >> e >> p;
		clear_lut(n);

		std::cerr << "start" << std::endl;

		// resize the queue and fill with numbers
		queue.resize(n);
		std::iota(std::begin(queue), std::end(queue), 1);

		std::sort(queue.begin(), queue.end(), comparer);

		// print out the result
		for (auto i = queue.begin(); i != queue.end(); ++i)
			std::cout << *i << ' ';

		// wipe out the pointer to holded elements,
		// but not the capacity.
		queue.clear();

		std::cerr << std::endl << std::endl;
	}

	return 0;
}
