#include <iostream>
#include <random>

const int max = 100;
int main()
{
    int n;
    std::cout << "Enter number of array elements (1-" << max << "):\n";
    std::cin >> n;

    if (!std::cin || (n < 1) || (n > max))
    {
        std::cout << "Invalid input. Try again";
        return 1;
    }

    double *arr = new double[max];

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
        double a, b;
        std::cout << "Enter interval borders [a, b]:\n";
        std::cout << "a = ";
        std::cin >> a;
        std::cout << "b = ";
        std::cin >> b;

        if (a > b)
        {
            double temp = a;
            a = b;
            b = temp;
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(a, b);
        for (int i = 0; i < n; i++)
        {
            arr[i] = dist(gen);
        }

        std::cout << "Array was filled with random numbers from [" << a << ", " << b << "]\n";
    }
    else
    {
        std::cout << "Invalid input\n";
        delete[] arr;
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

    int count = 0;

    for (int i = 0; i < n; i++)
    {
        bool unique = true;

        for (int k = 0; k < i; k++)
        {
            if (arr[i] == arr[k])
            {
                unique = false;
                break;
            }
        }
        if (unique)
        {
            count++;
        }
    }
    std::cout << "Amount of different elements is: " << count << std::endl;

    double firstNegative = -1, lastNegative = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
        {
            firstNegative = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (arr[i] < 0)
        {
            lastNegative = i;
            break;
        }
    }
    double sum = 0;
    if (firstNegative != lastNegative && firstNegative != -1 && lastNegative != -1)
    {
        for (int i = firstNegative + 1; i <= lastNegative - 1; i++)
        {
            sum += arr[i];
        }
    }
    std::cout << "Sum between first and last negative elements is: " << sum << std::endl;

    double x;
    std::cout << "Enter number X: ";
    std::cin >> x;

    int newSize = 0;
    for (int i = 0; i < n; i++)
    {
        double abs_num = arr[i];
        if (abs_num < 0)
        {
            abs_num = -abs_num;
        }
        if (abs_num > x)
        {
            arr[newSize] = arr[i];
            newSize++;
        }
    }
    for (int i = newSize; i < n; i++)
    {
        arr[i] = 0.0;
    }
    std::cout << "Compressed array (elements with |value| > " << x << "): [";
    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i];
        if (i < n - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
    std::cout << "Number of remaining elements: " << newSize << std::endl;
    std::cout << "Number of removed elements: " << n - newSize << std::endl;

    return 0;
}