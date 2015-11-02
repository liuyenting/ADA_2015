#include <iostream>

#define MAX_DIGITS 18
/*
 * 1) position of the higest digit
 * 2) highest digit
 * 3) mod 7
 * 4) number of digit 7
 * 5) number of digit 4
 *
 * Position of the digit shall starts from 1.
 */
unsigned long long table[MAX_DIGITS+1][10][7][MAX_DIGITS+1][MAX_DIGITS+1];

unsigned long long pow(int base, int exponent) {
	unsigned long long result = 1;
	while(exponent-- > 0)
		result *= base;
	return result;
}

void fill_table(void) {
	// the initial conditions.
	for(auto digit = 0; digit <= 9; digit++) {
		table[1][digit][digit%7][(digit == 7) ? 1 : 0][(digit == 4) ? 1 : 0] = 1;
	}

	#ifdef TABLE
	std::cout << "=== START TABLE GENERATION ===" << std::endl;
	#endif

	// fill from the lowest digit.
	for(auto digit_pos = 2; digit_pos <= MAX_DIGITS; digit_pos++) {
		for(auto curr_digit = 0; curr_digit <= 9; curr_digit++) {
			for(auto mod = 0; mod < 7; mod++) {
				for(auto seven_cnt = 0; seven_cnt <= digit_pos; seven_cnt++) {
					for(auto four_cnt = 0; four_cnt <= digit_pos; four_cnt++) {
						// mod 7 when ONLY consider the highest digit.
						int curr_mod = (curr_digit * pow(10, digit_pos-1)) % 7;
						int prev_mod = mod - curr_mod; prev_mod += (prev_mod < 0) ? 7 : 0;

						// lookup the table and write into the new cell.
						unsigned long long prev_val = 0;
						for(auto prev_digit = 0; prev_digit <= 9; prev_digit++) {
							switch(curr_digit) {
							case 4:
								prev_val += (four_cnt) ? table[digit_pos-1][prev_digit][prev_mod][seven_cnt][four_cnt-1] : 0;
								break;
							case 7:
								prev_val += (seven_cnt) ? table[digit_pos-1][prev_digit][prev_mod][seven_cnt-1][four_cnt] : 0;
								break;
							default:
								prev_val += table[digit_pos-1][prev_digit][prev_mod][seven_cnt][four_cnt];
							}
						}
						table[digit_pos][curr_digit][mod][seven_cnt][four_cnt] = prev_val;

						#ifdef TABLE
						if((digit_pos <= 3) && (curr_digit == 7))
							std::cout << "table[" << digit_pos << "][" << curr_digit << "][" << mod << "][" << seven_cnt << "][" << four_cnt << "] = " << table[digit_pos][curr_digit][mod][seven_cnt][four_cnt] << std::endl;
						#endif
					}
				}
			}
		}
	}

	#ifdef TABLE
	std::cout << "=== END TABLE GENERATION ===" << std::endl;
	#endif
}

unsigned long long count_lucky_numbers(int digit_pos, int curr_digit, int acc_mod, int curr_seven_cnt, int curr_four_cnt) {

	std::cout << curr_digit << " @ pos " << digit_pos << ", acc_mod = " << acc_mod << ", n7 = " << curr_seven_cnt << ", n4 = " << curr_four_cnt << std::endl;

	unsigned long long result = 0;

	for(auto trial_digit = 0; trial_digit < curr_digit; trial_digit++) {
		// calculate what the previous remainder should be to fulfill the accumulated mod result.
		int curr_mod = (trial_digit * pow(10, digit_pos-1)) % 7;
		int prev_mod = acc_mod - curr_mod; prev_mod += (prev_mod < 0) ? 7 : 0;

		std::cout << " > searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << std::endl;

		// calculate the number limitation of digits.
		switch(trial_digit) {
		case 4:
			for(auto seven_cnt = (curr_seven_cnt >= 3) ? 0 : (3 - curr_seven_cnt);
			    seven_cnt <= (MAX_DIGITS - curr_seven_cnt);
			    seven_cnt++)
			{
				for(auto four_cnt = 0; four_cnt + curr_four_cnt + 1 < seven_cnt + curr_seven_cnt; four_cnt++) {
					result += table[digit_pos][trial_digit][prev_mod][seven_cnt][four_cnt];
					std::cout << " >> searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt; // << std::endl;
					std::cout << "... " << result << std::endl;
				}
			}
			break;
		case 7:
			for(auto seven_cnt = (curr_seven_cnt >= 2) ? 0 : (2 - curr_seven_cnt);
			    seven_cnt <= (MAX_DIGITS - curr_seven_cnt - 1);
			    seven_cnt++)
			{
				for(auto four_cnt = 0; four_cnt + curr_four_cnt < seven_cnt + curr_seven_cnt + 1; four_cnt++) {
					result += table[digit_pos][trial_digit][prev_mod][seven_cnt][four_cnt];
					std::cout << " >> searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt; // << std::endl;
					std::cout << "... " << result << std::endl;
				}
			}
			break;
		default: for(auto seven_cnt = (curr_seven_cnt >= 3) ? 0 : (3 - curr_seven_cnt);
			            seven_cnt <= (MAX_DIGITS - curr_seven_cnt);
			            seven_cnt++)
			{
				for(auto four_cnt = 0; four_cnt + curr_four_cnt < seven_cnt + curr_seven_cnt; four_cnt++) {
					result += table[digit_pos][trial_digit][prev_mod][seven_cnt][four_cnt];
					std::cout << " >> searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt; // << std::endl;
					std::cout << "... " << result << std::endl;
				}
			}
		}

		std::cout << "... " << result << std::endl;
	}

	std::cout << "... " << result << " found" << std::endl;

	return result;
}

unsigned long long count_lucky_numbers(unsigned long long boundary) {
	if(boundary < 777) {
		return 0;
	} else if(boundary <= 1000) {
		return 1;
	}

	unsigned long long result = 0;
	int digits[MAX_DIGITS+1] = {0};

	// parse the integer to digits.
	int digit_pos;
	for(digit_pos = 1; boundary > 0; digit_pos++, boundary /= 10) {
		digits[digit_pos] = boundary % 10;
	}
	// remove the exceeded position after the increment(++).
	--digit_pos;

	// std::cout << digit_pos << " digits" << std::endl;

	// collect the result from the highest digit.
	int acc_mod = 0, seven_cnt = 0, four_cnt = 0;
	for(; digit_pos > 0; digit_pos--) {
		// std::cout << digits[digit_pos] << " @ pos " << digit_pos << ", acc_mod = " << acc_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt << std::endl;

		// increment the seven/four counter if needed.
		switch(digits[digit_pos]) {
		case 4:
			four_cnt++;
			break;
		case 7:
			seven_cnt++;
			break;
		}

		// lookup the table for current result.
		result += count_lucky_numbers(digit_pos, digits[digit_pos], acc_mod, seven_cnt, four_cnt);

		// calculate the previous remainder.
		// int curr_mod = (digits * pow(10, digit_pos-1)) % 7;
		// int prev_mod = mod - curr_mod; prev_mod += (prev_mod < 0) ? 7 : 0;

		// calculate the accumulated mod result.
		acc_mod += digits[digit_pos] * pow(10, digit_pos-1); acc_mod %= 7;
	}

	// count current number in test as well (on-boundary).
	if((acc_mod == 0) && (seven_cnt >= 3) && (seven_cnt > four_cnt))
		result++;

	return result;
}

int main(void) {
	fill_table();

	#ifndef TEST

	int cases;
	std::cin >> cases;

	unsigned long long lb, ub;
	while(cases-- > 0) {
		std::cin >> lb >> ub;

		std::cout << (count_lucky_numbers(ub) - count_lucky_numbers(lb-1)) << std::endl;
	}

	#else

	// 777, 7077, 7707, 7770, 7777
	unsigned long long test = 10700;
	std::cout << test << " has " << count_lucky_numbers(test) << " lucky numbers" << std::endl;

	#endif

	return 0;
}
