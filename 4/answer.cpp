#include <stdio.h>
#include <string.h>
#include <iostream>
unsigned long long int dp[19][10][7][19][19];

int tens_mod_7[19];

void make_tens_mod_7() {
	tens_mod_7[0] = 1;
	for(int i = 1; i < 19; ++i) {
		tens_mod_7[i] = (tens_mod_7[i-1] * 10) % 7;
	}
}

void make_dp_table( ) {
	// initialize dp table
	memset( dp, 0, sizeof(dp) );
	//dp[0][0][0][0][0] = 1;
	for(int i = 0; i < 10; i++) {
		dp[1][i][i%7][(i==7)][(i==4)] = 1;
	}
	for(int n_digit = 1; n_digit <= 18; ++n_digit) {
		for(int last_number = 0; last_number < 10; ++last_number) {
			int last_mod_7 = (last_number * tens_mod_7[n_digit-1]) % 7;
			for(int mod_7 = 0; mod_7 < 7; ++mod_7) {
				int overall_mod_7 = (last_mod_7 + mod_7) % 7;
				if(last_number == 4) {
					for(int n_4 = 1; n_4 <= 18; ++n_4) {
						for(int n_7 = 0; n_7 <= 18; ++n_7) {
							dp[n_digit][last_number][overall_mod_7][n_7][n_4]
							 += dp[n_digit-1][last_number][mod_7][n_7][n_4 - 1];
						}
					}
				} else if(last_number == 7) {
					for(int n_4 = 0; n_4 <= 18; ++n_4) {
						for(int n_7 = 1; n_7 <= 18; ++n_7) {
							dp[n_digit][last_number][overall_mod_7][n_7][n_4]
							 += dp[n_digit-1][last_number][mod_7][n_7-1][n_4];
						}
					}
				} else {
					for(int n_4 = 0; n_4 <= 18; ++n_4) {
						for(int n_7 = 0; n_7 <= 18; ++n_7) {
							dp[n_digit][last_number][overall_mod_7][n_7][n_4]
							 += dp[n_digit-1][last_number][mod_7][n_7][n_4];
						}
					}
				}
			}
		}
	}
}

void init() {
	make_tens_mod_7();
	make_dp_table();
}
/*
 * unsigned long long int n_lucky_tens( int first_number, int exp, int plus_mod_7, int plus_n_7, int plus_n_4 ) {
 * unsigned long long int result = 0;
 * for(int last_number = 0; last_number < first_number; ++last_number) {
 * int last_mod_7 = (last_number * tens_mod_7[exp]) % 7;
 * int previous_mod_7 = (7 - ((last_mod_7 + plus_mod_7)%7) ) % 7;
 * if(last_number == 4) {
 * for(int n_7 = plus_n_7 >= 3 ? 0 : 3 - plus_n_7;
 *     n_7 <= 18 - plus_n_7; ++n_7)
 * {
 *  for(int n_4 = 0; n_4 + plus_n_4 + 1 < n_7 + plus_n_7; ++n_4) {
 *   result += dp[exp][previous_mod_7][n_7][n_4];
 *  }
 * }
 * } else if(last_number == 7) {
 * for(int n_7 = plus_n_7 >= 2 ? 0 : 2 - plus_n_7;
 *     n_7 <= 18 - plus_n_7 - 1; ++n_7)
 * {
 *  for(int n_4 = 0; n_4 + plus_n_4 < n_7 + plus_n_7 + 1; ++n_4) {
 *   result += dp[exp][previous_mod_7][n_7][n_4];
 *  }
 * }
 * } else {
 * for(int n_7 = plus_n_7 >= 3 ? 0 : 3 - plus_n_7;
 *     n_7 <= 18 - plus_n_7; ++n_7)
 * {
 *  for(int n_4 = 0; n_4 + plus_n_4< n_7 + plus_n_7; ++n_4) {
 *   result += dp[exp][previous_mod_7][n_7][n_4];
 *  }
 * }
 * }
 * }
 * // // Check first_number * 10^exp itself:
 * // if( first_number == 7 ){
 * //     plus_n_7 += 1;
 * // }
 * // else if( first_number == 4 ){
 * //     plus_n_4 += 1;
 * // }
 * // plus_mod_7 += first_number * tens_mod_7[exp];
 * // plus_mod_7 %= 7;
 * // if( plus_n_7 > plus_n_4 && plus_mod_7 == 0 && plus_n_7 >= 3 && first_number != 0 ){
 * //     result += 1;
 * // }
 * return result;
 * }
 *
 * unsigned long long int n_lucky( unsigned long long int upper_bound ) {
 * int digits[19];
 * int n_digit = 0;
 * while(upper_bound > 0) {
 * digits[n_digit] = upper_bound % 10;
 * upper_bound /= 10;
 * n_digit += 1;
 * }
 * int n_4 = 0, n_7 = 0, mod_7 = 0;
 * unsigned long long int result = 0;
 * for(int i = n_digit - 1; i >= 0; --i) {
 * result += n_lucky_tens( digits[i], i, mod_7, n_7, n_4 );
 * if(digits[i] == 4) {
 * n_4 += 1;
 * }
 * if(digits[i] == 7) {
 * n_7 += 1;
 * }
 * mod_7 += digits[i] * tens_mod_7[i];
 * mod_7 %= 7;
 * }
 * if(mod_7 == 0 && n_7 > n_4 && n_7 >= 3) {
 * result += 1;
 * }
 * return result;
 * }
 */

int main() {
	//int n_test_cases;
	//scanf("%d", &n_test_cases );
	init();
	std::cout << dp[1][7][0][1][0] << std::endl;
	return 0;
	/*
	 * for(int nth_test = 0; nth_test < n_test_cases; ++nth_test) {
	 * unsigned long long int lower_bound, upper_bound;
	 * scanf("%llu %llu", &lower_bound, &upper_bound );
	 * printf( "%llu\n", n_lucky( upper_bound ) - n_lucky( lower_bound -1 ) );
	 * }
	 */
}
