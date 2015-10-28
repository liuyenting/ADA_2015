#include <iostream>

#define MAX_DIGITS 18

/* 10^n % 7 */
static const int exp10_mod7_lookup[19] = {
	1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1, 3, 2, 6, 4, 5, 1
};

/*
 * 1) current digits (starts from 1)
 * 2) digit 0~9
 * 2) mod 7
 * 3) amount of digit 7
 * 4) amount of digit 4
 */
static int table[MAX_DIGITS+1][10][7][MAX_DIGITS+1][MAX_DIGITS+1];

void generate_table(void) {
	// write the default condition.
	table[0][0][0][0][0] = 1;

	// filling rest of the digits.
	int digit_pos, digit, mod, seven_cnt, four_cnt;
	for(digit_pos = 1; digit_pos <= MAX_DIGITS; digit_pos++) {
		for(digit = 0; digit <= 9; digit++) {
			int new_mod = ((digit % 7) * exp10_mod7_lookup[digit_pos - 1]) % 7;
			for(mod = 0; mod < 7; mod++) {
				for(seven_cnt = 0; seven_cnt <= digit_pos; seven_cnt++) {
					for(four_cnt = 0; four_cnt <= digit_pos; four_cnt++) {
						if(mod < new_mod)
							new_mod = 7 + mod - new_mod;
						else
							new_mod = mod - new_mod;

						int pulled_value = 0;
						switch(digit) {
						case 4:
							pulled_value = (four_cnt) ? (table[digit_pos - 1][digit][new_mod][seven_cnt][four_cnt - 1]) : 0;
							break;
						case 7:
							pulled_value = (seven_cnt) ? (table[digit_pos - 1][digit][new_mod][seven_cnt - 1][four_cnt]) : 0;
							break;
						default:
							pulled_value = table[digit_pos - 1][digit][new_mod][seven_cnt][four_cnt];
						}
						table[digit_pos][digit][mod][seven_cnt][four_cnt] += pulled_value;
					}
				}
			}
		}
	}
}

int count_lucky_numbers(int digit, int digit_pos, int mod, int seven_cnt, int four_cnt) {
	int result = 0;

	// overwrite mod as 0.
	//mod = 0;

	std::cout << "testing table[" << digit_pos << "][" << mod << "][" << seven_cnt << "][" << four_cnt << "]..." << std::endl;

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
		buffer[digit_pos] = boundary % 10;      // asm will use the quotient/remainder from the same instr.
	digit_pos--; // remove the additional 1, added on the last cycle.

	// lb: lower bound; ub: upper bound
	int seven_lb, seven_ub;
	int four_lb, four_ub;
	for(; digit_pos > 0; digit_pos--) {
		std::cout << "testing digit " << buffer[digit_pos] << "..." << std::endl;

		four_cnt += (digit == 4);
		seven_cnt += (digit == 7);

		for(int i = 3; i <= seven_cnt; i++) {
			for(int j = 0; j < i; j++) {
				result += table[digit_pos][buffer[digit_pos]][0][i][j];
			}
		}
	}

	return result;
}

int main(void) {
	generate_table();

	// start the lookup.
	unsigned long long lower_bound, upper_bound;
	lower_bound = 7710, upper_bound = 10000;

	std::cout << table[4][7][0][0][0] << std::endl;
	std::cout << table[4][7][0][1][0] << std::endl;
	std::cout << table[4][7][0][2][0] << std::endl;
	std::cout << table[4][7][0][3][0] << std::endl;
	std::cout << table[4][7][0][4][0] << std::endl;
	std::cout << table[4][7][0][5][0] << std::endl;
	std::cout << table[4][7][0][6][0] << std::endl;
	std::cout << table[4][7][0][7][0] << std::endl;

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
