#include <iostream>

int main(void) {
	unsigned long long val = 1;
	for(int i = 0; i <= 18; i++) {
		std::cout << val << ',' << std::endl;
		val *= 10;
	}
	return 0;
}
