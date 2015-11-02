#include <iostream>

int checksum(int num) {
	int chksum = 0;
	while(num > 0) {
		chksum += num % 10;
		num /= 10;
	}
	return chksum;
}

int main(void) {
	int cases;
	std::cin >> cases;

	int days;
	int *checksums;
	while(cases-- > 0) {
		std::cin >> days;

		// read the checksums.
		checksums = (int*)malloc(sizeof(int) * days);
		for(int i = 0; i < days; i++)
			std::cin >> checksums[i];

		int incomings = 0;
		for(int i = 0; i < days; i++) {
			while(checksum(incomings) != checksums[i])
				incomings++;
			std::cout << incomings;
			if(i != days-1)
				std::cout << ' ';
			else
				std::cout << std::endl;
		}

		delete [] checksums;
	}

	return 0;
}
