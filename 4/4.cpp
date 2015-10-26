#include <iostream>
#include <vector>

struct prefix {
	unsigned int level;
	unsigned long long value;
	//unsigned int remainder;
	unsigned int seven;
	unsigned int four;
};

static const unsigned int remainder_lookup[7][10] = {
	{ 0, 1, 2, 3, 4, 5, 6, 0, 1, 2 },
	{ 3, 4, 5, 6, 0, 1, 2, 3, 4, 5 },
	{ 6, 0, 1, 2, 3, 4, 5, 6, 0, 1 },
	{ 2, 3, 4, 5, 6, 0, 1, 2, 3, 4 },
	{ 5, 6, 0, 1, 2, 3, 4, 5, 6, 0 },
	{ 1, 2, 3, 4, 5, 6, 0, 1, 2, 3 },
	{ 4, 5, 6, 0, 1, 2, 3, 4, 5, 6 }
};

static unsigned int upper_digits;
static unsigned long long lower, upper;
static unsigned int lower_result, upper_result;

static struct prefix number[1024];

int main(void) {
	// disable buffering
	std::ios_base::sync_with_stdio(false);

	unsigned int cases;
	std::cin >> cases;

	while(cases-- > 0) {
		std::cin >> lower >> upper;

		// test for digits.
		unsigned long long mask = 1;
		upper_digits = 0;
		for(unsigned int i = 0; i <= 18; i++, mask *= 10) {
			if(!upper_digits && mask >= upper)
				upper_digits = i;
		}
		upper_digits--;

		lower_result = upper_result = 0;

		struct prefix old_prefix;
		int index = 0;

		// push the first element.
		for(unsigned int i = 0; i <= 9; i++) {
			number[index++] = {
				.level = 1,
				.value = i,
				//.remainder = i%7,
				.seven = (i==7),
				.four = (i==4)
			};
		}

		while(index > 0) {
			old_prefix = number[--index];

			if(old_prefix.level > upper_digits) {
				if((old_prefix.seven >= 3) && (old_prefix.seven > old_prefix.four) && (old_prefix.value % 7 == 0)) {
					//std::cerr << old_prefix.value << std::endl;
					if(old_prefix.value < upper)
						upper_result++;
					if(old_prefix.value < lower)
						lower_result++;
				}
			} else {
				for(unsigned int i = 0; i <= 9; i++) {
					number[index++] = {
						.level = old_prefix.level + 1,
						.value = old_prefix.value*10 + i,
						//.remainder = remainder_lookup[old_prefix.remainder][i],
						.seven = old_prefix.seven + (i==7),
						.four = old_prefix.four + (i==4)
					};
				}
			}
		}

		//std::cerr << "upper result = " << upper_result << std::endl;
		//std::cerr << "lower result = " << lower_result << std::endl;
		//std::cerr << "[" << lower << "," << upper << "] = ";
		std::cout << (upper_result-lower_result) << std::endl;
	}

	return 0;
}
