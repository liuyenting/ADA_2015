#include <iostream>

int main(void) {
	for(int i = 0; i < 7; i++) {
		std::cout << "{ ";
		for(int j = 0; j <= 9; j++) {
			int val = i*10+j;
			std::cout << val%7;
			if(j !=9)
				std::cout << ",";
			std::cout << " ";
		}
		std::cout << "}," << std::endl;
	}
	return 0;
}
