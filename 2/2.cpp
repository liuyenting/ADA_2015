#include <iostream>

#define VAR_MAX 1000

int main()
{
	int cases;
	std::cin >> cases;

	int a, b, x;
	int max;
	while (cases > 0)
	{
		std::cin >> x;

		// Wrap the maximum possibility for a, b.
		if (x > VAR_MAX)
		{
			max = VAR_MAX;
		}
		else
		{
			max = x;
		}

		std::cout << max << ' ' << (x-max) << std::endl;

		--cases;
	}

	return 0;
}
