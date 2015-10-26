#include <iostream>
#include <vector>
#include <stack>

struct prefix {
	unsigned int level;
	unsigned long long value;
	unsigned int remainder;
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

static unsigned int lower_digits, upper_digits;
static unsigned long long lower, upper;
static unsigned int counter, lower_result, upper_result;

/*
 * void count_lucky_numbers(unsigned int digits, struct prefix prefix) {
 * if(digits > upper_digits) {
 * if((prefix.remainder == 0) && (prefix.seven >= 3) && (prefix.seven > prefix.four)) {
 * //std::cerr << prefix.value << std::endl;
 *
 * upper_result++;
 * if(prefix.value < lower)
 *  lower_result++;
 * }
 *
 * return;
 * }
 *
 * for(unsigned int i = 0; i <= 9; i++) {
 * struct prefix new_prefix = {
 * .value = prefix.value*10+i,
 * .remainder = remainder_lookup[prefix.remainder][i],
 * .seven = prefix.seven+(i==7),
 * .four = prefix.four+(i==4)
 * };
 *
 * count_lucky_numbers(digits+1, new_prefix);
 * }
 * }
 */

void count_lucky_numbers() {
	counter = lower_result = upper_result = 0;

	struct prefix old_prefix, new_prefix;
	std::vector<struct prefix> number;
	number.reserve(1024);

	// push the first element.
	for(unsigned int i = 0; i <= 9; i++) {
		new_prefix = {
			.level = 1,
			.value = i,
			.remainder = i%7,
			.seven = (i==7),
			.four = (i==4)
		};
		number.push_back(new_prefix);
	}

	unsigned long long depth = 0;

	while(!number.empty()) {
		//if(number.size() > depth)
		//	depth = number.size();

		old_prefix = number.back();
		number.pop_back();

		if(old_prefix.level > upper_digits) {
			if((old_prefix.remainder == 0) && (old_prefix.seven >= 3) && (old_prefix.seven > old_prefix.four)) {
				//std::cerr << old_prefix.value << std::endl;
				if(old_prefix.value < upper)
					upper_result++;
				if(old_prefix.value < lower)
					lower_result++;
			}
		} else {
			for(unsigned int i = 0; i <= 9; i++) {
				new_prefix = {
					.level = old_prefix.level + 1,
					.value = old_prefix.value*10 + i,
					.remainder = remainder_lookup[old_prefix.remainder][i],
					.seven = old_prefix.seven + (i==7),
					.four = old_prefix.four + (i==4)
				};
				number.push_back(new_prefix);
			}
		}
	}

	//std::cerr << "maximum depth = " << depth << std::endl;
}

/*
 * void count_lucky_numbers() {
 * lower_result = upper_result = 0;
 * for(unsigned int i = 0; i <= 9; i++) {
 * struct prefix prefix = {
 * .value = i,
 * .remainder = i%7,
 * .seven = (i==7),
 * .four = (i==4)
 * };
 *
 * count_lucky_numbers(1, prefix);
 * }
 * }
 */

int main(void) {
	// disable buffering
	std::ios_base::sync_with_stdio(false);

	unsigned int cases;
	std::cin >> cases;

	while(cases-- > 0) {
		std::cin >> lower >> upper;

		// test for digits.
		unsigned long long mask = 1;
		lower_digits = upper_digits = 0;
		for(unsigned int i = 0; i <= 18; i++, mask *= 10) {
			//std::cerr << "testing i = " << i << ", mask = " << mask << std::endl;
			if(!lower_digits && mask >= lower)
				lower_digits = i;
			if(!upper_digits && mask >= upper)
				upper_digits = i;
		}
		upper_digits--;

		count_lucky_numbers();

		//std::cerr << "upper result = " << upper_result << std::endl;
		//std::cerr << "lower result = " << lower_result << std::endl;
		//std::cerr << "[" << lower << "," << upper << "] = ";
		std::cout << (upper_result-lower_result) << std::endl;

		//std::cerr << "l digits = " << min_digits << std::endl;
		//std::cerr << "r digits = " << lower_digits << std::endl;
	}

	return 0;
}
