#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota

#define MAX_N 200000

unsigned long long pow_n_mod(unsigned int base, unsigned long long exponent, unsigned long modulus)
{
	/*
	   // get the highest bit.
	   unsigned long long mult_bit;
	   if (exponent == 0)
	   mult_bit = 0;
	   else
	   mult_bit = 1 << (8*sizeof(unsigned long long) - __builtin_clzll(exponent) - 1);
	   unsigned long long product = 1, tmp = n;

	   std::cerr << "exponent = " << exponent << " -> mult_bit = " << mult_bit << std::endl;

	   for (mult_bit >>= 1; mult_bit > 0; mult_bit >>=1)
	   {
	   tmp *= tmp;
	   if ((mult_bit & exponent) != 0)
	   tmp *= n;

	   //tmp %= modulus;

	   std::cerr << "tmp = " << tmp << std::endl;

	   product *= tmp % modulus;
	   }
	   product %= modulus;

	   return product;
	 */

	unsigned long long product = 1;

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

struct queue_comparer
{
	unsigned int n;              // number of people
	unsigned long c, p;          // c:constant, p:modulus, p2:criterion
	unsigned long long e;        // e:exponent

	bool operator()(const unsigned long long& i, const unsigned long long& j)
	{
		// ab mod n = ((a mod n)(b mod n)) mod n;
		unsigned long long var = ( ((c*(i-j)) % p) * (pow_n_mod(i+j, e, p)) ) % p;

		std::cerr << "i = " << i << ", j = " << j << std::endl;
		std::cerr << c << "*(" << i << "-" << j << ")%" << p << " = " << (c*(i-j)) % p << std::endl;
		std::cerr << "( (" << i << "+" << j << ")^" << e << " )%" << p << " = " << pow_n_mod(i+j, e, p) << std::endl;
		std::cerr << "(a*b) % p = " << var << std::endl << std::endl;

		// var > 2*p -> 2*var > p
		return 2 * var > p;
	}
};

int main(void)
{
	int cases;
	std::cin >> cases;

	// pre-allocate the maximum possible size of the queue.
	std::vector<unsigned int> queue;
	queue.reserve(MAX_N);

	// setup the comparer.
	queue_comparer comparer;

	while (cases-- > 0)
	{
		std::cerr << "cases " << (cases+1) << std::endl;

		// read the values and prep them.
		std::cin >> comparer.n >> comparer.c >> comparer.e >> comparer.p;

		// resize the queue and fill with numbers
		queue.resize(comparer.n);
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
