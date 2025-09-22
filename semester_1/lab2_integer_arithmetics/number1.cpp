#include <iostream>

int main()
{
    int min = 9;
    int n;
    std::cout << "Введите натуральное число n: ";
    std::cin >> n;
    if (n <= 0) 
    {
        std::cout << "Число должно быть натуральным (положительным)" << std::endl;
        return 1;
    }
    int original = n;
    while (n)
    {
        int a = n % 10;
        if (a < min)
            min = a;
        n /= 10;
    }
    n = original;
    int newNum = 0, mult = 1;
    while (n)
    {
        int a = n % 10;
        if (a != min)
        {
            newNum = a * mult + newNum;
            mult *= 10;
        }
        n /= 10;
    }
    std::cout << "Минимальная цифра числа: " << min << std::endl;
    std::cout << "Новое число: " << newNum;
    return 0;
}