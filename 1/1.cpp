#include <iostream>

int main()
{
    int cases;
    std::cin >> cases;
    
    long a, b;
    for(int i = 0; i < cases; i++)
    {
        std::cin >> a >> b;
        std::cout << (a+b) << std::endl;
    }

    return 0;
}
