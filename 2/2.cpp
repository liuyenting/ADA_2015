#include <iostream>

#define VAR_MAX 1000

int main()
{
	int cases;
	std::cin >> cases;

	int x, max;
	while (cases > 0)
	{
		std::cin >> x;

		// Wrap the maximum possibility for a, b.
		max = (x > VAR_MAX) ? VAR_MAX : x;

		std::cout << max << ' ' << (x-max) << std::endl;

		--cases;
	}

	return 0;
}
