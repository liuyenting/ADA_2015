#include <iostream>

int main(void) {
	unsigned long long val = 1;
	for(int i = 0; i <= 18; i++, val *= 10) {
		for(int j = 0; j <= 9; j++) {
			std::cout << "{ ";
			for(int k = 0; k <= 9; k++) {
				std::cout << ((j*val + k) % 7);
				if(k != 9)
					std::cout << ", ";
				else
					std::cout << ' ';
			}
			std::cout << "}, " << std::endl;
		}
	}
	std::cout << std::endl;
	return 0;
}
