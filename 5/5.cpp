#include <iostream>
#include <vector>

#define MAX_DIGITS 1000

int main(void) {
	int days;
	std::cin >> days;

	std::vector<int> chksum(days);
	for(int day = 0; day < days; day++)
		std::cin >> chksum[day];

	// Maximum of 1000 digits.
	std::vector<int> digits(MAX_DIGITS);
	int digit_pos = 0;

	int prev_chksum, curr_chksum, delta_chksum;
	for(int day = 0; day < days; day++) {
		if(day == 0) {
			// Set the first checksum directly on the first day.
			digits[digit_pos++] = chksum[0];
		} else {
			curr_chksum = chksum[day];
			if(curr_chksum > prev_chksum) {
				// std::cerr << '>' << std::endl;

				// Calculate how many checksum are required.
				delta_chksum = curr_chksum - prev_chksum;

				// Fill the lower digits as 9.
				int fill_pos;
				for(fill_pos = 0; fill_pos < digit_pos && delta_chksum > 0; fill_pos++) {
					delta_chksum -= 9 - digits[fill_pos];
					digits[fill_pos] = 9;
				}

				// Check whether the fillings are enough.
				if(delta_chksum > 9) {
					// This case only occurs when carry out is needed.
					for(; fill_pos < MAX_DIGITS && delta_chksum > 0; fill_pos++) {
						digits[fill_pos] = 9;
						delta_chksum -= digits[fill_pos];
					}
				}
				if(delta_chksum > 0) {
					digits[fill_pos++] = delta_chksum;
				} else if(delta_chksum < 0) {
					// Too many 0, decrease the most significant digit.
					digits[fill_pos-1] += delta_chksum;
				}

				// Update the digit boundary.
				if(fill_pos > digit_pos)
					digit_pos = fill_pos;
			} else if(curr_chksum <= prev_chksum) {
				// std::cerr << "<=" << std::endl;

				// Gradually carry out the digits until checksum is smaller.
				for(int i = 0; i < MAX_DIGITS; i++) {
					// Wipe current digit.
					prev_chksum -= digits[i];
					digits[i] = 0;

					// Carry to the next digit, and handle the overflows.
					int carry = 1;
					for(int j = i+1; j < digit_pos && carry > 0; j++) {
						// Carry in and update the checksum.
						if(digits[j] + carry > 9) {
							prev_chksum += 9 - digits[j];
							carry -= 9 - digits[j];
							digits[j] = 9;
						} else {
							prev_chksum += carry;
							digits[j] += carry;
							carry = 0;
						}
					}

					// Increase the digit boundary if overflow.
					if(carry > 0) {
						prev_chksum += carry;
						digits[digit_pos++] += carry;
					}

					if(prev_chksum <= curr_chksum)
						break;
				}

				// Fill rest of the needed checksum.
				delta_chksum = curr_chksum - prev_chksum;
				for(int i = 0; i < digit_pos && delta_chksum > 0; i++) {
					digits[i] = 9;
					delta_chksum -= 9;
					if(delta_chksum < 0) {
						digits[i] += delta_chksum;
						delta_chksum = 0;
					}
				}
			}
		}

		// Update previous checksum.
		prev_chksum = chksum[day];

		// Print out the result.
		for(int i = digit_pos - 1; i >= 0; i--)
			std::cout << digits[i];

		// Print out the delimiters.
		if(day != days - 2)
			std::cout << ' ';
		else
			std::cout << std::endl;
	}

	return 0;
}
