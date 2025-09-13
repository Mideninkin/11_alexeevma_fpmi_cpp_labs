#include <iostream>

int main()
{
    int n, sum = 0, pro = 1;
    std::cin >> n;
    for (; n > 0; n--)
    {
        if (n % 2)
        {
            pro *= n;
        }
        else
        {
            sum += n;
        }
    }
    std::cout << sum << " " << pro;
    return 0;
}
