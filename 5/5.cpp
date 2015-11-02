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

int increase_by_one(int (&digits)[MAX_DIGIT]) {
	digits[0]++;

	int chksum = 0, carry = 0;
	// carry out the numbers.
	for(int j = 0; j < MAX_DIGIT; j++) {
		digits[j] += carry;
		carry = digits[j] / 10;
		digits[j] %= 10;

		chksum += digits[j];
	}
	return chksum;
}

void print_digits(int (&digits)[MAX_DIGIT]) {
	bool leading_zero = true;
	for(int j = MAX_DIGIT-1; j >= 0; j--) {
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
	/*
	   int test = 123, chksum, tmp;

	   chksum = checksum(test);
	   std::cout << "checksum of " << test << " is " << chksum << ".\n";

	   int digits[MAX_DIGIT] = {0};
	   tmp = test;
	   for(int i = 0; i < MAX_DIGIT; i++) {
	   digits[i] = tmp%10;
	   tmp /= 10;
	   }

	   chksum = increase_by_one(digits);
	   std::cout << "checksum of increase_by_one(" << test << ") = ";
	   print_digits(digits);
	   std::cout << " is " << chksum << ".\n";

	   return 0;
	 */

	int cases;
	std::cin >> cases;

	int days;
	int *checksums;
	int checksum;
	while(cases-- > 0) {
		std::cin >> days;

		// read the checksums.
		checksums = (int*)malloc(sizeof(int) * days);
		for(int i = 0; i < days; i++)
			std::cin >> checksums[i];

		int digits[MAX_DIGIT] = {0};

		// int incomings = 0;
		for(int i = 0; i < days; i++) {
			// calculate current checksum.
			checksum = 0;
			for(int j = 0; j < MAX_DIGIT; j++)
				checksum += digits[j];

			// force the increment, since s is strictly increasing.
			if(checksum == checksums[i])
				checksum = increase_by_one(digits);

			// search for next valid value.
			while(checksum != checksums[i])
				checksum = increase_by_one(digits);
			print_digits(digits);

			// decide whether we should print the white space.
			if(i != days-1)
				std::cout << ' ';
			else
				std::cout << std::endl;
		}

		delete [] checksums;
	}

	return 0;
}
