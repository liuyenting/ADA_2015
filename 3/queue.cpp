#include <iostream>
#include <vector>

#define MAX_N 200000
int main(void)
{
	int cases;
	std::cin >> cases;

	unsigned int n;            // number of people
	unsigned long c, p;        // c:constant, p:modulus
	unsigned long long e;      // e:exponent

	// pre-allocate the maximum possible size of the queue.
	std::vector<unsigned int> queue;
	queue.reserve(MAX_N);

	while (cases-- > 0)
	{
		// read the values.
		std::cin >> n >> c >> e >> p;



		// wipe out the pointer to holded elements,
		// but not the capacity.
		queue.clear();
	}

	return 0;
}

unsigned long long pow(unsigned int n, unsigned long long exponent){
	// get the highest bit.
	unsigned long long mult_bit = 8*sizeof(unsigned long long) -
	                              __builtin_clzll(exponent);
	unsigned long long product = n;

	for (mult_bit >>= 1; mult_bit > 0; mult_bit >>=1)
	{
		product *= product;
		if ((mult_bit & exponent) != 0)
			product *= n;
	}

	return product;
}
