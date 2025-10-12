#include <iostream>
#include <random>
#include <ctime>

void input (int* x, int min, int max)
{
    int d;
    while (!(std::cin >> d) || (d < min) || (d > max))
    {
        std::cout << "Invalid input" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    *x = d;
}

void Swap( int *q, int *o)
{
    int temp = *q;
    *q = *o;
    *o = temp;
}

void OutputOfArray(int* arr, int n)
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

int Multiplicate (int* arr, int n)
    {
        int mult = 1;
    for (int i = 1; i < n; i += 2)
        {
            mult *= *(arr + i);
        }
    return mult;
    }    

int SumBetweenNilElements(int* arr, int n)
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
    if (firstNil != lastNil && firstNil != -1 && lastNil != -1)
    {
        for (int i = firstNil + 1; i <= lastNil - 1; i++)
        {
            sum += *(arr + i);
        }
    }
    return sum;
}

void NewArray (int* arr, int n)
    {
        for (int i = 0; i < n - 1; i++)
        {
            if ((*(arr + i) > 0) && (*(arr + i + 1) < 0))
            {
                Swap(arr + 1, arr + i + 1);
            }
        }
    }
int main()
{
 const int max = 100;
    int n;
    int arr[max];

    std::cout << "Enter number of array elements (1-" << max << "):\n";

    input (&n, 1, 100);

    std::cout << "Number of elements: " << n << std::endl;

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
    {    std::cout << "Enter interval borders [a, b]:\n";
        
        std::cout << "a = ";
    while (!(std::cin >> a))
    {
        std::cout << "Invalid input for a. Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "b = ";
    while (!(std::cin >> b))
    {
        std::cout << "Invalid input for b. Please enter an integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
        if (a > b)
        {
            Swap(&a, &b);
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
        std::cout << "Invalid input\n";
        return 1;
    }
    
    OutputOfArray(arr, n);

    int mult = Multiplicate(arr, n);
    std::cout << "Product of even numbered elements is: " << mult << std::endl;
    
    int sum = SumBetweenNilElements(arr, n);
    std::cout << "Sum between first and last nil elements is: " << sum << std::endl;

    NewArray(arr, n);

    std::cout << "Modifieded array: [";
    for (int i = 0; i < n; i++)
    {
        std::cout << *(arr + i);
        if (i < n - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";

    return 0;
}

