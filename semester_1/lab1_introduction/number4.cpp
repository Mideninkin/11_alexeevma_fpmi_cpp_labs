#include <iostream>

int main()
{
    int k, even = 1, odd = 1;
    std::cin >> k;
    for (int i = 1; i <= k; i++)
    {
        if (i % 2)
        {
            odd *= i;
        }
        else
        {
            even *= i;
        }
    }
    std::cout << odd << " " << even;
    return 0;

}

