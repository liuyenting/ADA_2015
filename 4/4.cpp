#include <iostream>

#define MAX_DIGITS 18

/* 10^n % 7 */
static const unsigned int exponent_ratio_lookup[19] = {
	1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1
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

/*
 * 1) current digits (starts from 1)
 * 2) mod 7
 * 3) amount of digit 7
 * 4) amount of digit 4
 */
static unsigned int table[MAX_DIGITS+1][7][MAX_DIGITS+1][MAX_DIGITS+1];

int main(void) {
	// write the default conditions.
	table[0][0][0][0] = 1;

	// filling rest of the digits.
	unsigned int digit_pos, mod, seven_cnt, four_cnt, digit;
	for(digit_pos = 1; digit_pos <= MAX_DIGITS; digit_pos++) {
		for(mod = 0; mod < 7; mod++) {
			for(seven_cnt = 0; seven_cnt <= digit_pos; seven_cnt++) {
				for(four_cnt = 0; four_cnt <= digit_pos; four_cnt++) {
					for(digit = 0; digit <= 9; digit++) {
						unsigned int new_mod = ((digit % 7) * exponent_ratio_lookup[digit_pos]) % 7;
						//unsigned long long new_mod = (digit * ratio[digit_pos]) % 7;

						if(mod < new_mod)
							new_mod = 7 + mod - new_mod;
						else
							new_mod = mod - new_mod;

						unsigned int pulled_value = 0;
						switch(digit) {
						case 4:
							pulled_value = (four_cnt) ? (table[digit_pos - 1][new_mod][seven_cnt][four_cnt - 1]) : 0;
							break;
						case 7:
							pulled_value = (seven_cnt) ? (table[digit_pos - 1][new_mod][seven_cnt - 1][four_cnt]) : 0;
							break;
						default:
							pulled_value = table[digit_pos - 1][new_mod][seven_cnt][four_cnt];
						}

						table[digit_pos][mod][seven_cnt][four_cnt] += pulled_value;
					}
				}
			}
		}
	}

	// start the lookup.
	unsigned long long lower_bound, upper_bound;

	lower_bound = 800, upper_bound = 10000;

	// DEBUG test
	unsigned int result = 0;
	digit_pos = 18;
	for(seven_cnt = 3; seven_cnt <= digit_pos; seven_cnt++) {
		for(four_cnt = 0; four_cnt < seven_cnt; four_cnt++) {
			unsigned int pulled = table[digit_pos][0][seven_cnt][four_cnt];
			//if(pulled > 0)
			//	std::cerr << "digit_pos = " << digit_pos << ", seven_cnt = " << seven_cnt << ", four_cnt = " << four_cnt << ", pulled = " << pulled << std::endl;

			result += pulled;
		}
	}
	std::cout << "result = " << result << std::endl;

	return 0;
}
