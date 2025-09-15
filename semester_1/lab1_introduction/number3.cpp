#include <iostream>

int main()
{
    int n, sum = 0;
    std::cin >> n;
    for (int i = 1; i <= n; i += 1)
    {
        sum += i * i;
    }
    std::cout << sum;
    return 0;
}
// Если число превышает диапазон, то оно не сможет храниться в целочисленном данных (int) (максимальное выводимое значение - 332833500)//