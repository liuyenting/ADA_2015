#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota

#define MAX_N 200000

unsigned long long pow(unsigned int n, unsigned long long exponent){
	// get the highest bit.
	unsigned long long mult_bit = 8*sizeof(unsigned long long) - __builtin_clzll(exponent);
	unsigned long long product = n;

	for (mult_bit >>= 1; mult_bit > 0; mult_bit >>=1)
	{
		product *= product;
		if ((mult_bit & exponent) != 0)
			product *= n;
	}

	return product;
}

struct queue_comparer
{
	unsigned int n;            // number of people
	unsigned long c, p;       // c:constant, p:modulus, p2:criterion
	unsigned long long e;      // e:exponent

	bool operator()(const unsigned long long& i, const unsigned long long& j)
	{
		unsigned long long var = c * (i-j) * pow(i+j, e);
		unsigned long long mod_var = var % p;

		std::cerr << "-> " << c << " * " << "( " << i << " - " << j <<" )"
		          << " * ( " << i << " + " << j << " ) ^ " << e
		          << " = " << var << std::endl;
		std::cerr << "   " << var << " mod " << p << " = " << mod_var
		          << " > " << ((float)p/2) << "? "
		          << ((2 * mod_var > p) ? "TRUE" : "FALSE") << std::endl;

		return 2 * mod_var < p;
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
