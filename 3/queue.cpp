#include <iostream>
#include <vector>
#include <algorithm> // std::sort
#include <iterator>  // std::begin, std::end
#include <numeric>   // std::iota

#define MAX_N 200000

unsigned long long pow_n_mod(unsigned int base, unsigned long long exponent, unsigned long modulus)
{
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

	bool operator()(const unsigned long long& j, const unsigned long long& i)
	{
		// ab mod n = ((a mod n)(b mod n)) mod n;
		long long var = ( ((c*(i-j)) % p) * (pow_n_mod(i+j, e, p)) ) % p;

		std::cerr << "i = " << i << ", j = " << j << std::endl;
		std::cerr << "-> " << c << "*(" << i << "-" << j << ")%" << p << " = " << (c*(i-j)) % p << std::endl;
		std::cerr << "-> ( (" << i << "+" << j << ")^" << e << " )%" << p << " = " << pow_n_mod(i+j, e, p) << std::endl;
		std::cerr << "-> (a*b)%" << p << " = " << var << std::endl << std::endl;

		// var > 2*p -> 2*var > p
		return 2 * var > p;
	}
};
// setup the comparer.
queue_comparer comparer;

std::vector<unsigned int> merge(std::vector<unsigned int> &vec,
                                const std::vector<unsigned int>& left,
                                const std::vector<unsigned int>& right)
{
	// Fill the resultant vector with sorted results from both vectors
	std::vector<unsigned int> result;
	unsigned left_it = 0, right_it = 0;

	while (left_it < left.size() && right_it < right.size())
	{
		// If the left value is smaller than the right it goes next
		// into the resultant vector
		/*
		   if (left[left_it] < right[right_it])
		   {
		   result.push_back(left[left_it]);
		   left_it++;
		   }
		   else
		   {
		   result.push_back(right[right_it]);
		   right_it++;
		   }
		 */

		if (comparer(left[left_it], right[right_it]))
		{
			result.push_back(right[right_it]);
			right_it++;
		}
		else
		{
			result.push_back(left[left_it]);
			left_it++;
		}
	}

	// Push the remaining data from both vectors onto the resultant
	while (left_it < left.size())
	{
		result.push_back(left[left_it]);
		left_it++;
	}

	while (right_it < right.size())
	{
		result.push_back(right[right_it]);
		right_it++;
	}
	// show merge process
	int i;
	for (i=0; i<result.size(); i++)
	{
		std::cout << result[i] << " ";
	}
	// break each line for display purposes
	std::cout << "***********" << std::endl;

	// take a source vector and parse the result to it. then return it.
	vec = result;
	return vec;
}

std::vector<unsigned int> merge_sort(std::vector<unsigned int>& vec)
{
	// terminate when list only contains a single element
	if (vec.size() == 1)
		return vec;

	// determine the location of the middle element in the vector
	std::vector<unsigned int>::iterator middle = vec.begin() + (vec.size() / 2);

	std::vector<unsigned int> left(vec.begin(), middle);
	std::vector<unsigned int> right(middle, vec.end());

	// perform a merge sort on the two smaller vectors
	left = merge_sort(left);
	right = merge_sort(right);

	return merge(vec,left, right);
}



int main(void)
{
	int cases;
	std::cin >> cases;

	// pre-allocate the maximum possible size of the queue.
	std::vector<unsigned int> queue;
	queue.reserve(MAX_N);



	while (cases-- > 0)
	{
		std::cerr << "cases " << (cases+1) << std::endl;

		// read the values and prep them.
		std::cin >> comparer.n >> comparer.c >> comparer.e >> comparer.p;

		// resize the queue and fill with numbers
		queue.resize(comparer.n);
		std::iota(std::begin(queue), std::end(queue), 1);

		std::sort(queue.begin(), queue.end(), comparer);
		//merge_sort(queue);

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
