#include <iostream>

#define MAX_DIGITS 18

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

//%
int tens_mod_7[19];
void make_tens_mod_7() {
	tens_mod_7[0] = 1;
	for(int i = 1; i < 19; ++i) {
		tens_mod_7[i] = (tens_mod_7[i-1] * 10) % 7;
	}
}
//%

/* 10^n % 7 */
static const int exp10_mod7_lookup[19] = {
	1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1
};

/*
 * 1) current digits (starts from 1)
 * 2) mod 7
 * 3) amount of digit 7
 * 4) amount of digit 4
 */
static int table[MAX_DIGITS+1][7][MAX_DIGITS+1][MAX_DIGITS+1];

void generate_table(void) {
	// write the default condition.
	table[0][0][0][0] = 1;

	// filling rest of the digits.
	int digit_pos, mod, seven_cnt, four_cnt, digit;
	for(digit_pos = 1; digit_pos <= MAX_DIGITS; digit_pos++) {
		for(mod = 0; mod < 7; mod++) {
			for(seven_cnt = 0; seven_cnt <= digit_pos; seven_cnt++) {
				for(four_cnt = 0; four_cnt <= digit_pos; four_cnt++) {
					for(digit = 0; digit <= 9; digit++) {
						//int new_mod = ((digit % 7) * exp10_mod7_lookup[digit_pos - 1]) % 7;
						unsigned long long new_mod = (digit * ratio[digit_pos]) % 7;

						if(mod < new_mod)
							new_mod = 7 + mod - new_mod;
						else
							new_mod = mod - new_mod;

						int pulled_value = 0;
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
}

unsigned long long int n_lucky_tens( int first_number, int exp, int plus_mod_7, int plus_n_7, int plus_n_4 ) {
	unsigned long long int result = 0;
	for(int last_number = 0; last_number < first_number; ++last_number) {
		int last_mod_7 = (last_number * tens_mod_7[exp]) % 7;
		int previous_mod_7 = (7 - ((last_mod_7 + plus_mod_7)%7) ) % 7;

		if(last_number == 4) {
			for(int n_7 = plus_n_7 >= 3 ? 0 : 3 - plus_n_7;
			    n_7 <= 18 - plus_n_7; ++n_7)
			{
				for(int n_4 = 0; n_4 + plus_n_4 + 1 < n_7 + plus_n_7; ++n_4) {
					result += table[exp][previous_mod_7][n_7][n_4];
				}
			}
		} else if(last_number == 7) {
			for(int n_7 = plus_n_7 >= 2 ? 0 : 2 - plus_n_7;
			    n_7 <= 18 - plus_n_7 - 1; ++n_7)
			{
				for(int n_4 = 0; n_4 + plus_n_4 < n_7 + plus_n_7 + 1; ++n_4) {
					result += table[exp][previous_mod_7][n_7][n_4];
				}
			}
		} else {
			for(int n_7 = plus_n_7 >= 3 ? 0 : 3 - plus_n_7;
			    n_7 <= 18 - plus_n_7; ++n_7)
			{
				for(int n_4 = 0; n_4 + plus_n_4< n_7 + plus_n_7; ++n_4) {
					result += table[exp][previous_mod_7][n_7][n_4];
				}
			}
		}
	}

	return result;
}

unsigned long long int n_lucky( unsigned long long int upper_bound ) {
	int digits[19];
	int n_digit = 0;
	while(upper_bound > 0) {
		digits[n_digit] = upper_bound % 10;
		upper_bound /= 10;
		n_digit += 1;
	}

	int n_4 = 0, n_7 = 0, mod_7 = 0;
	unsigned long long int result = 0;
	for(int i = n_digit - 1; i >= 0; --i) {
		result += n_lucky_tens( digits[i], i, mod_7, n_7, n_4 );
		if(digits[i] == 4) {
			n_4 += 1;
		}
		if(digits[i] == 7) {
			n_7 += 1;
		}
		mod_7 += digits[i] * tens_mod_7[i];
		mod_7 %= 7;
	}
	if(mod_7 == 0 && n_7 > n_4 && n_7 >= 3) {
		result += 1;
	}
	return result;
}

int count_lucky_numbers(int digit, int digit_pos, int mod, int seven_cnt, int four_cnt) {
	int result = 0;

	int curr_digit, curr_mod, prev_mod;
	for(curr_digit = 0; curr_digit < digit; curr_digit++) {
		curr_mod = ((curr_digit % 7) * exp10_mod7_lookup[digit_pos]) % 7;

		if(mod < curr_mod)
			prev_mod = 7 + mod - curr_mod;
		else
			prev_mod = mod - curr_mod;

		//std::cout << "trial number = " << curr_digit << ", previous mod = " << prev_mod << std::endl;
	}

	return result;
}

int count_lucky_numbers(unsigned long long boundary) {
	int result = 0;
	int digit_pos, digit, mod = 0, seven_cnt = 0, four_cnt = 0;

	// parse the boundary into digits set, big-endian.
	int buffer[MAX_DIGITS+1] = {0};
	for(digit_pos = 1; boundary > 0; boundary /= 10, digit_pos++)
		buffer[digit_pos] = boundary % 10; // asm will use the quotient/remainder from the same instr.
	digit_pos--; // remove the additional 1, added on the last cycle.

	std::cout << "digits = " << digit_pos << std::endl;

	// start from 1 order less.
	for(; digit_pos > 0; digit_pos--) {
		digit = buffer[digit_pos];
		std::cout << " > digit = " << digit << std::endl;

		// get the result of previous stage.
		result += count_lucky_numbers(digit, digit_pos-1, mod, seven_cnt, four_cnt);

		// increment the counters.
		four_cnt += (digit == 4);
		seven_cnt += (digit == 7);
		mod += ((digit % 7) * exp10_mod7_lookup[digit_pos]) % 7;
		std::cout << "...appended mod = " << (((digit % 7) * exp10_mod7_lookup[digit_pos]) % 7) << std::endl;
		mod %= 7;

		// verify whether current number is a lucky number as well?
		if((seven_cnt >= 3) && (seven_cnt > four_cnt) && (mod == 0))
			result++;

		//std::cout << "digit_pos = " << digit_pos << ", result = " << result << std::endl;
	}

	return result;
}

int main(void) {
	make_tens_mod_7();
	generate_table();

	int cases;
	std::cin >> cases;

	// start the lookup.
	unsigned long long lower_bound, upper_bound;
	while(cases-- > 0) {
		std::cin >> lower_bound >> upper_bound;
		std::cout << (n_lucky(upper_bound) - n_lucky(lower_bound-1)) << std::endl;
	}
	//std::cout << count_lucky_numbers(lower_bound) << std::endl;
	return 0;

	// DEBUG test
	/*
	 * int result = 0;
	 * digit_pos = 18;
	 * for(seven_cnt = 3; seven_cnt <= digit_pos; seven_cnt++) {
	 * for(four_cnt = 0; four_cnt < seven_cnt; four_cnt++) {
	 * int pulled = table[digit_pos][0][seven_cnt][four_cnt];
	 * //if(pulled > 0)
	 * //	std::cout << "digit_pos = " << digit_pos << ", seven_cnt = " << seven_cnt << ", four_cnt = " << four_cnt << ", pulled = " << pulled << std::endl;
	 *
	 * result += pulled;
	 * }
	 * }
	 * std::cout << "result = " << result << std::endl;
	 */
	return 0;
}
