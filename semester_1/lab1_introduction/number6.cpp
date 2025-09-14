#include <iostream>

int main()
{
    int n, sum = 0;
    std::cin >> n;
    for (int i = 1; i <= 2 * n; i += 2)
    {
        sum += n;
    }
    std::cout << sum;
    return 0;
}