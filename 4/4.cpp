#include <iostream>
#include <cstdint>

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
static const uint64_t M = 0x71c71c71c71c71c7;
static const uint64_t Q[7] = {30, 15, 9, 3, 3, 3, 3};
static const uint64_t R[7] = {0x3fffffff, 0x00007fff, 0x000001ff, 0x00000007, 0x00000007, 0x00000007, 0x00000007};

int main(void) {
	int cases;
	std::cin >> cases;

	uint64_t l, r;

	uint64_t n;        // numerator
	uint64_t m;        // n % d goes here.

	uint8_t seven, four, dummy;
	uint64_t c, t;

	while(cases-- > 0) {
		c = 0;
		std::cin >> l >> r;

		for(n = l; n <= r; n++) {
			// mod 7
			// 7 = (1 << 3) - 1
			m = (n & M) + ((n >> 3) & M);

			for(const uint64_t * q = &Q[0], * r = &R[0]; m > 7; q++, r++) {
				m = (m >> *q) + (m & *r);
			}
			//m = m == 7 ? 0 : m;        // OR, less portably: m = m & -((signed)(m - d) >> s);

			if(m == 7) {
				seven = four = 0;
				for(t = n; t > 0; t /= 10) {
					dummy = t % 10;
					seven += (dummy == 7);
					four += (dummy == 4);
				}

				c += ((seven > four) && (seven > 2));
			}
		}

		std::cout << c << std::endl;
	}

	return 0;
}
