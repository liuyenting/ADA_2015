#include <iostream>
#include <cstdint>
#include <vector>

/*
 * 0111000111000111000111000111000111000111000111000111000111000111
 *
 *                                   000111000111000111000111000111 (30)
 *                               0111000111000111000111000111000111
 *
 *                                                  111000111000111 (15)
 *                                              0111000111000111000
 *
 *                                                        000111000 (9)
 *                                                       0111000111
 *
 *                                                             111 (3)
 *                                                         0111000
 *
 *                                                             000 (3)
 *                                                            0111
 *
 *                                                             111 (3)
 *                                                               0
 *
 *                                                               0 (3)
 *                                                               x
 */

// ...for mod 7
static const uint64_t M = 0x71c71c71c71c71c7;
static const uint64_t Q[7] = {30, 15, 9, 3, 3, 3, 3};
static const uint64_t R[7] = {0x3fffffff, 0x00007fff, 0x000001ff, 0x00000007, 0x00000007, 0x00000007, 0x00000007};

int main(void) {
	// disable buffering
	std::ios_base::sync_with_stdio(false);

	int cases;
	std::cin >> cases;

	uint64_t l, r;

	uint64_t n;        // numerator
	uint64_t m;        // n % d goes here

	int8_t seven, four, dummy;
	uint64_t c, t;

	uint8_t greater = 0;
	std::vector<uint64_t> list;

	while(cases-- > 0) {
		std::cin >> l >> r;

		// check the first one...
		// mod 7, 7 = (1 << 3) - 1
		m = (l & M) + ((l >> 3) & M);

		for(const uint64_t *q = &Q[0], *r = &R[0]; m > 7; q++, r++) {
			m = (m >> *q) + (m & *r);
		}
		//m = (m == 7) ? 0 : m;
		// less portably:
		//m = m & -((signed)(m - d) >> s);

		// wrap around
		m = 7-m;

		/// ...bump by 7
		for(n = l+m, c = 0; n <= r; n += 7) {

			for(t = n, seven = four = 0; t > 0; t /= 10) {
				dummy = t % 10;
				seven += (dummy == 7);
				four += (dummy == 4);
			}

			if((seven >= 3) && (seven > four)) {
				//std::cerr << n << std::endl;
				c++;

				//if(seven > 4) {
				//	greater++;
				list.push_back(n);
				//}
			}

			//c += (seven >= 3) && (seven > four);
		}

		std::cerr << std::endl;
		//std::cerr << "greater than 4 ? " << greater << std::endl;
		for(auto itr = list.begin(); itr != list.end(); ++itr)
			std::cerr << *itr << std::endl;
		std::cerr << "total = " << c << std::endl;
	}

	return 0;
}
