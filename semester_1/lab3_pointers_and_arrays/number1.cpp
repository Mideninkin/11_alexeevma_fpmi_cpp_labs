#include <iostream>
#include <random>

const int max = 100;
int main()
{
    int n;
    int arr[max];

    std::cout << "Enter number of array elements (1-" << max << "):\n";
    std::cin >> n;

    if (!(std::cin) || (n < 1) || (n > max))
    {
        std::cout << "Invalid input. Try again";
        return 1;
    }

    char answer;
    std::cout << "What input do you choose: 'M' or 'A'? ";
    std::cin >> answer;

    if (answer == 'M' || answer == 'm')
    {
        std::cout << "Enter " << n << " integer numbers:\n";
        for (int i = 0; i < n; i++)
        {
            std::cout << "Element [" << i << "]: ";
            std::cin >> arr[i];
        }
    }
    else if (answer == 'A' || answer == 'a')
    {
        int a, b;
        std::cout << "Enter interval borders [a, b]:\n";
        std::cout << "a = ";
        std::cin >> a;
        std::cout << "b = ";
        std::cin >> b;

        if (a > b)
        {
            int temp = a;
            a = b;
            b = temp;
        }
        std::mt19937 gen(45218965);
        std::uniform_int_distribution<int> dist(a, b);
        int x = dist(gen);

        for (int i = 0; i < n; i++)
        {
            arr[i] = dist(gen);
        }

        std::cout << "Array was filled with random numbers from [" << a << ", " << b << "]\n";
    }
    else
    {
        std::cout << "Invalid input\n";
        return 1;
    }

    std::cout << "Array: [";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i];
        if (i < n - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";

    int mult = 1;
    for (int i = 1; i < n; i += 2)
    {
        mult *= arr[i];
    }
    std::cout << "Product of even-numbered elements: " << mult << "\n";

    int firstNil = -1, lastNil = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            firstNil = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] == 0)
        {
            lastNil = i;
            break;
        }
    }
    int sum = 0;
    if (firstNil != lastNil && firstNil != -1 && lastNil != -1)
    {
        for (int i = firstNil + 1; i <= lastNil - 1; i++)
        {
            sum += arr[i];
        }
    }
    std::cout << "Sum between first and last nil elements is: " << sum << std::endl;

    for (int i = 0; i < n - 1; i++)
    {
        if ((arr[i] > 0) && (arr[i + 1] < 0))
        {
            int k = arr[i];
            arr[i] = arr[i + 1];
            arr[i + 1] = k;
        }
    }
    std::cout << "Modifieded array: [";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i];
        if (i < n - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}