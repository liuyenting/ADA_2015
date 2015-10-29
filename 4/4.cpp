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
int table[MAX_DIGITS+1][10][7][MAX_DIGITS+1][MAX_DIGITS+1];

unsigned long long pow(int base, int exponent) {
	unsigned long long result = 1;
	while(exponent-- > 0)
		result *= base;
	return result;
}

void fill_table(void) {
	// the initial condition.
	//table[0][0][0][0][0] = 1;
	for(auto digit = 0; digit <= 9; digit++) {
		table[1][digit][digit%7][(digit == 7) ? 1 : 0][(digit == 4) ? 1 : 0] = 1;
	}

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
						int prev_val;
						for(auto prev_digit = 0; prev_digit <= 9; prev_digit++) {
							switch(curr_digit) {
							case 4:
								prev_val = (four_cnt) ? table[digit_pos-1][prev_digit][prev_mod][seven_cnt][four_cnt-1] : 0;
								break;
							case 7:
								prev_val = (seven_cnt) ? table[digit_pos-1][prev_digit][prev_mod][seven_cnt-1][four_cnt] : 0;
								break;
							default:
								prev_val = table[digit_pos-1][prev_digit][prev_mod][seven_cnt][four_cnt];
							}
							table[digit_pos][curr_digit][mod][seven_cnt][four_cnt] += prev_val;
						}
					}
				}
			}
		}
	}
}

int count_lucky_numbers(int digit_pos, int curr_digit, int acc_mod, int curr_seven_cnt, int curr_four_cnt) {

	//std::cout << curr_digit << " @ pos " << digit_pos << ", acc_mod = " << acc_mod << ", n7 = " << curr_seven_cnt << ", n4 = " << curr_four_cnt << std::endl;

	int result = 0;

	for(auto trial_digit = 0; trial_digit < curr_digit; trial_digit++) {
		// calculate what the previous remainder should be to fulfill the accumulated mod result.
		int curr_mod = (trial_digit * pow(10, digit_pos-1)) % 7;
		int prev_mod = acc_mod - curr_mod; prev_mod += (prev_mod < 0) ? 7 : 0;

		//std::cout << " > searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << std::endl;

		// calculate the number limitation of digits.
		int seven_cnt_lb = 3, seven_cnt_ub = MAX_DIGITS - curr_seven_cnt;
		int four_cnt_lb = 0, four_cnt_ub = 0;
		switch(trial_digit) {
		case 4:
			if(curr_seven_cnt >= 3)
				seven_cnt_lb = 0;
			else
				seven_cnt_lb = 3 - curr_seven_cnt;

			for(auto seven_cnt = seven_cnt_lb; seven_cnt <= seven_cnt_ub; seven_cnt++) {
				for(auto four_cnt = 0; four_cnt + curr_four_cnt + 1 < seven_cnt + curr_seven_cnt; four_cnt++) {
					result += table[digit_pos][trial_digit][prev_mod][seven_cnt][four_cnt];
					//std::cout << " > searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt << std::endl;
				}
			}
			break;
		case 7:
			if(curr_seven_cnt >= 2)
				seven_cnt_lb = 0;
			else
				seven_cnt_lb = 2 - curr_seven_cnt;
			seven_cnt_ub--;

			for(auto seven_cnt = seven_cnt_lb; seven_cnt <= seven_cnt_ub; seven_cnt++) {
				for(auto four_cnt = 0; four_cnt + curr_four_cnt < seven_cnt + curr_seven_cnt + 1; four_cnt++) {
					result += table[digit_pos][trial_digit][prev_mod][seven_cnt][four_cnt];
					//std::cout << " > searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt << std::endl;
				}
			}
			break;
		default:
			if(curr_seven_cnt >= 3)
				seven_cnt_lb = 0;
			else
				seven_cnt_lb = 3 - curr_seven_cnt;

			for(auto seven_cnt = seven_cnt_lb; seven_cnt <= seven_cnt_ub; seven_cnt++) {
				for(auto four_cnt = 0; four_cnt + curr_four_cnt < seven_cnt + curr_seven_cnt; four_cnt++) {
					result += table[digit_pos][trial_digit][prev_mod][seven_cnt][four_cnt];
					//std::cout << " > searching " << trial_digit << " @ pos " << digit_pos << ", mod = " << prev_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt << std::endl;
				}
			}
		}

		//std::cout << "... " << result << std::endl;
	}

	//std::cout << "... " << result << " found" << std::endl;

	return result;
}

int count_lucky_numbers(unsigned long long boundary) {
	int result = 0;
	int digits[MAX_DIGITS+1] = {0};

	// parse the integer to digits.
	int digit_pos;
	for(digit_pos = 1; boundary > 0; digit_pos++, boundary /= 10) {
		digits[digit_pos] = boundary % 10;
	}
	// remove the exceeded position after the increment(++).
	--digit_pos;

	//std::cout << digit_pos << " digits" << std::endl;

	// collect the result from the highest digit.
	int acc_mod = 0, seven_cnt = 0, four_cnt = 0;
	for(; digit_pos > 0; digit_pos--) {
		//std::cout << digits[digit_pos] << " @ pos " << digit_pos << ", acc_mod = " << acc_mod << ", n7 = " << seven_cnt << ", n4 = " << four_cnt << std::endl;

		// lookup the table for current result.
		result += count_lucky_numbers(digit_pos, digits[digit_pos], acc_mod, seven_cnt, four_cnt);

		// increment the seven/four counter if needed.
		switch(digits[digit_pos]) {
		case 4:
			four_cnt++;
			break;
		case 7:
			seven_cnt++;
			break;
		}

		// calculate the previous remainder.
		//int curr_mod = (digits * pow(10, digit_pos-1)) % 7;
		//int prev_mod = mod - curr_mod; prev_mod += (prev_mod < 0) ? 7 : 0;

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

	int cases;
	std::cin >> cases;

	unsigned long long lb = 999, ub = 10000;
	while(cases-- > 0) {
		std::cin >> lb >> ub;
		std::cout << (count_lucky_numbers(ub) - count_lucky_numbers(lb-1)) << std::endl;
	}

	// 777, 7077, 7707, 7770, 7777
	//unsigned long long test = 10000;
	//std::cout << test << " has " << count_lucky_numbers(test) << " lucky numbers" << std::endl;

	return 0;
}
