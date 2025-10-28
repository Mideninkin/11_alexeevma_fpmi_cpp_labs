#include <iostream>
#include <random>
#include <ctime>

void Input(int &x, int min)
{
    int d;
    while (!(std::cin >> d) || (d < min))
    {
        std::cout << "Invalid input" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    x = d;
}

void OutputOfArray(int *arr, int n)
{
    std::cout << "Array: [";
    for (int i = 0; i < n; i++)
    {
        std::cout << *(arr + i);
        if (i < n - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}

int Multiplicate(int *arr, int n)
{
    int mult = 1;
    for (int i = 1; i < n; i += 2)
    {
        mult *= *(arr + i);
    }
    return mult;
}

int SumBetweenNilElements(int *arr, int n)
{
    int firstNil = -1, lastNil = -1;
    for (int i = 0; i < n; i++)
    {
        if (*(arr + i) == 0)
        {
            firstNil = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (*(arr + i) == 0)
        {
            lastNil = i;
            break;
        }
    }
    int sum = 0;
    if (!(firstNil - lastNil))
    {
    std::cout << "First and last nil are neighboring elements";
    }
    if (firstNil != lastNil && firstNil != -1 && lastNil != -1)
    {
        for (int i = firstNil + 1; i <= lastNil - 1; i++)
        {
            sum += *(arr + i);
        }
    }
    return sum;


}

void NewArray(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if ((*(arr + i) > 0) && (*(arr + i + 1) < 0))
        {
            std::swap(*(arr + 1), *(arr + i + 1));
        }
    }
}

void DecideTypeOfInput(int *arr, int n)
{
    char answer;
    std::cout << "What input do you choose: 'M' or 'A'? ";
    std::cin >> answer;

    int a, b;
    switch (answer)
    {
    case 'M':
    case 'm':
    {
        std::cout << "Enter " << n << " integer numbers:\n";
        for (int i = 0; i < n; i++)
        {
            std::cout << "Element [" << i << "]: ";
            std::cin >> arr[i];
        }
        break;
    }
    case 'A':
    case 'a':
    {
        std::cout << "Enter interval borders [a, b]:\n";

        std::cout << "a = ";
        Input(a, INT_MIN);
        std::cout << "b = ";
        Input(b, INT_MIN);
        if (a > b)
        {
            std::swap(a, b);
        }
        std::srand(std::time(0));
        for (int i = 0; i < n; i++)
        {
            int random_number = a + std::rand() % (b - a + 1);
            arr[i] = random_number;
        }

        std::cout << "Array was filled with random numbers from [" << a << ", " << b << "]\n";
        break;
    }
    default:
        std::cout << "Invalid input. Using automatic fill." << std::endl;
        std::srand(std::time(0));
        for (int i = 0; i < n; i++)
        {
            *(arr + i) = -50 + std::rand() % 100;
        }
    }
}
int main() {
const long long max = 10000000000000;
    int n;
    int arr[max];

    std::cout << "Enter number of array elements:\n";

    Input(n, 1);

    std::cout << "Number of elements: " << n << std::endl;
    DecideTypeOfInput(arr, n);
    OutputOfArray(arr, n);

    int mult = Multiplicate(arr, n);
    std::cout << "Product of even numbered elements is: " << mult << std::endl;

    int sum = SumBetweenNilElements(arr, n);
    std::cout << "Sum between first and last nil elements is: " << sum << std::endl;

    NewArray(arr, n);

    OutputOfArray(arr, n);

    return 0;
}
