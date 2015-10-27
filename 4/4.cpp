#include <iostream>
#include <vector>

struct prefix {
	unsigned int level;
	unsigned long long value;
	unsigned int seven;
	unsigned int four;
};

static const unsigned long long ratio[20] = {
	0,
	1,
	10,
	100,
	1000,
	10000,
	100000,
	1000000,
	10000000,
	100000000,
	1000000000,
	10000000000,
	100000000000,
	1000000000000,
	10000000000000,
	100000000000000,
	1000000000000000,
	10000000000000000,
	100000000000000000,
	1000000000000000000
};

static unsigned int upper_digits;
static unsigned long long lower, upper;
static unsigned int lower_result, upper_result;

static struct prefix number[1024];
static unsigned int DP[18][10];

int main(void) {
	// disable buffering
	std::ios_base::sync_with_stdio(false);

	unsigned int cases;
	std::cin >> cases;

	while(cases-- > 0) {
		std::cin >> lower >> upper;

		// test for digits.
		for(unsigned int i = 1; i < 19; i++) {
			if(ratio[i] >= upper) {
				upper_digits = i;
				break;
			}
		}
		upper_digits--; // no need for full set of digits

		lower_result = upper_result = 0;

		int index = 0;

		// push the first element.
		for(unsigned int i = 0; i <= 9; i++) {
			number[index++] = {
				.level = 1,
				.value = i,
				.seven = (i==7),
				.four = (i==4)
			};
		}

		while(index-- > 0) {
			if(number[index].level == upper_digits) {
				if((number[index].seven >= 3) && (number[index].seven > number[index].four) && (number[index].value % 7 == 0)) {
					//std::cerr << number[index].value << std::endl;
					upper_result += (number[index].value < upper);
					lower_result += (number[index].value < lower);
				}
			} else {
				// new item, i = 0
				number[index++].level += 1;

				// new items, i = 1~9
				for(unsigned int i = 1; i <= 9; i++, index++) {
					number[index].level = number[index-1].level;
					number[index].value = number[index-1].value + ratio[number[index].level];
					number[index].seven = number[index-1].seven;
					number[index].four = number[index-1].four;
				}

				// add back 4 and 7 counter.
				number[index-6].four++;
				number[index-3].seven++;
			}
		}

		//std::cerr << "upper result = " << upper_result << std::endl;
		//std::cerr << "lower result = " << lower_result << std::endl;
		//std::cerr << "[" << lower << "," << upper << "] = ";
		std::cout << (upper_result-lower_result) << std::endl;
	}

	return 0;
}
