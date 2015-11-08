#include <iostream>

#define MAX_DIGIT 16

int checksum(int num) {
	int chksum = 0;
	while(num > 0) {
		chksum += num % 10;
		num /= 10;
	}
	return chksum;
}

void print_digits(int digit_cnt, int (&digits)[MAX_DIGIT]) {
	// std::cout << "print_digits() called, max_digit = " << max_digit << std::endl;
	bool leading_zero = true;
	for(int j = digit_cnt-1; j >= 0; j--) {
		// don't print the leading zeros.
		if(digits[j] == 0) {
			if(leading_zero)
				continue;
		} else {
			if(leading_zero)
				leading_zero = false;
		}

		std::cout << digits[j];
	}
}

int main(void) {
	#ifdef DEBUG
	{
		int test = 123, chksum, tmp, max_digit;

		chksum = 0;
		tmp = test;
		while(tmp > 0) {
			chksum += tmp % 10;
			tmp /= 10;
		}
		std::cout << "checksum of " << test << " is " << chksum << ".\n";

		int digits[MAX_DIGIT] = {0};
		tmp = test;
		for(int i = 0; i < MAX_DIGIT; i++) {
			digits[i] = tmp%10;
			tmp /= 10;
		}

		chksum = increase_by_one(&max_digit, digits);
		std::cout << "checksum of increase_by_one(" << test << ") = ";
		print_digits(digits);
		std::cout << " is " << chksum << ".\n";

		return 0;
	}
	#endif

	int cases;
	std::cin >> cases;

	int days;
	int* checksums;
	while(cases-- > 0) {
		std::cin >> days;

		// read the checksums.
		checksums = (int*)malloc(sizeof(int) * days);
		for(int i = 0; i < days; i++)
			std::cin >> checksums[i];

		int digits[MAX_DIGIT] = {0}, digit_cnt;
		int prev_chksum, curr_chksum, carry;

		// complete the first case.
		curr_chksum = checksums[0];
		digit_cnt = curr_chksum/9 + 1;
		for(int i = 0; i < digit_cnt-1; i++)
			digits[i] = 9;
		digits[digit_cnt-1] = curr_chksum%9;

		// print the first case.
		print_digits(digit_cnt, digits);
		std::cout << ((days != 1) ? ' ' : '\n');

		// find rest of the cases.
		for(int i = 1; i < days; i++) {
			prev_chksum = curr_chksum;
			curr_chksum = checksums[i];

			int j, delta_chksum;
			if(prev_chksum > curr_chksum) {
				std::cout << '\n' << '>';

				bool complete;
				do
				{
					complete = true;

					int bnd;
					// find the first non-zero position.
					for(j = 0; j < MAX_DIGIT; j++) {
						if(digits[j] != 0) {
							bnd = j+1;
							break;
						}
					}
					// get the position next to it.
					++bnd;

					std::cout << "position boundary = " << bnd << ", digit is " << digits[bnd-1] << std::endl;

					// check whether more digits need to introduce here.
					digits[bnd-1]++;
					prev_chksum++;
					std::cout << "digits: ";
					print_digits(digit_cnt, digits);
					std::cout << ", chksum = " << prev_chksum << std::endl;
					// reset the lower digits.
					if(digits[bnd-1] > curr_chksum) {
						digits[bnd++] = 1;
						prev_chksum = 1;
						for(j = 0; j < bnd-1; j++)
							digits[j] = 0;
					} else {
						for(j = 0; j < bnd-1; j++) {
							prev_chksum -= digits[j];
							digits[j] = 0;
						}
					}

					// update digit count.
					if(bnd > digit_cnt)
						digit_cnt = bnd;

					std::cout << "digits: ";
					print_digits(digit_cnt, digits);
					std::cout << ", chksum = " << prev_chksum << std::endl;

					delta_chksum = curr_chksum-prev_chksum;
					for(j = 0; j < bnd; j++) {
						digits[j] += delta_chksum;
						if(digits[j] > 9) {
							delta_chksum = digits[j] - 9;
							digits[j] = 9;
						} else if(digits[j] < 0) {
							digits[j] = 0;
							complete = false;
						} else
							break;
					}
				} while(!complete);
/*
    // carry out.
    digits[digit_cnt-1]++;
    if(digits[digit_cnt-1] > 9) {
     digits[digit_cnt] = 1;
     digits[digit_cnt-1] = 0;
     digit_cnt++;
    }
    digits[digit_cnt++] = 1;
    for(int j = 0; j < digit_cnt-1; j++)
     digits[j] = 0;



    // remained delta checksum.
    delta_chksum = curr_chksum-1;

    for(j = 0; j < MAX_DIGIT; j++) {
     digits[j] += delta_chksum;
     if(digits[j] > 9) {
      delta_chksum = digits[j] - 9;
      digits[j] = 9;
     } else
      break;
    }
 */
			} else if(prev_chksum == curr_chksum) {
				std::cout << '=';

				int bnd;
				// find the first non-zero position.
				for(j = 0; j < MAX_DIGIT; j++) {
					if(digits[j] != 0) {
						bnd = j+1;
						break;
					}
				}
				// get the position next to it.
				++bnd;
				if(bnd > digit_cnt)
					digit_cnt = bnd;

				// std::cout << "position boundary = " << bnd << std::endl;

				// reset the lower digits.
				digits[bnd-1]++;
				for(j = 0; j < bnd-1; j++)
					digits[j] = 0;

				delta_chksum = curr_chksum-digits[bnd-1];
				for(j = 0; j < MAX_DIGIT; j++) {
					digits[j] += delta_chksum;
					if(digits[j] > 9) {
						delta_chksum = digits[j] - 9;
						digits[j] = 9;
					} else
						break;
				}
			} else {
				std::cout << '<';

				delta_chksum = curr_chksum-prev_chksum;

				for(j = 0; j < MAX_DIGIT; j++) {
					digits[j] += delta_chksum;
					if(digits[j] > 9) {
						delta_chksum = digits[j] - 9;
						digits[j] = 9;
					} else {
						++j;
						break;
					}
				}
				if(j > digit_cnt)
					digit_cnt = j;
			}

			print_digits(digit_cnt, digits);
			std::cout << ((i != days-1) ? ' ' : '\n');
		}
	}

	return 0;
}
