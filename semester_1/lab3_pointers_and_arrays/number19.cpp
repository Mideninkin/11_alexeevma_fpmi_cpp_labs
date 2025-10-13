#include <iostream>
#include <random>
#include <cmath>

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

void Swap( double *q, double *o)
{
    double temp = *q;
    *q = *o;
    *o = temp;
}

void OutputOfArray(double* arr, int n)
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

int Count (double* arr, int n)
    {
        int counter = 0;

    for (int i = 0; i < n; i++)
    {
        bool unique = true;

        for (int k = 0; k < i; k++)
        {
            if (*(arr + i) == *(arr + k))
            {
                unique = false;
                break;
            }
        }
        if (unique)
        {
            counter++;
        }
    }
        return counter;
    }

int MakeArray (double* arr, int n, double x)
    {
        int newArray = 0;

    for (int i = 0; i < n; i++)
    {
        double abs_num = *(arr + i);
        if (abs_num < 0)
        {
            abs_num = -abs_num;
        }
        if (abs_num > x)
        {
            *(arr + newArray) = *(arr + i);
            newArray++;
        }
    }
    for (int i = newArray; i < n; i++)
    {
        *(arr + i) = 0.0;
    }
    std::cout << "New array (elements with |value| > " << x << "): [";
    for (int i = 0; i < n; i++)
    {
        std::cout << *(arr + i);
        if (i < n - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
    return newArray;
    }

double SumBetweenNegatives(double* arr, int n)
    {
    int firstNegative = -1, lastNegative = -1;
    for (int i = 0; i < n; i++)
    {
        if (*(arr + i) < 0)
        {
            firstNegative = i;
            break;
        }
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (*(arr + i) < 0)
        {
            lastNegative = i;
            break;
        }
    }
    double sum = 0;
    if ((firstNegative != lastNegative) && (firstNegative != -1) && (lastNegative != -1))
    {
        for (int i = firstNegative + 1; i <= lastNegative - 1; i++)
        {
            sum += *(arr + i);
        }
    }
    return sum;
    }  
    
int main()
{
    const int max = 100;
    int n;

    std::cout << "Enter number of array elements (1-" << max << "):\n";

    input (&n, 1, 100);

    std::cout << "Number of elements: " << n << std::endl;

    char answer;
    std::cout << "What input do you choose: 'M' or 'A'? ";
    std::cin >> answer;

    double* arr = new double[max];

    double a, b;
    switch (answer)
    {
    case 'M':
    case 'm':
    {
        std::cout << "Enter " << n << " real numbers:\n";
        for (int i = 0; i < n; i++)
        {
            std::cout << "Element [" << i << "]: ";
            std::cin >> *(arr + i);
        }
        break;
    }
    case 'A':
    case 'a':
    {    std::cout << "Enter interval borders [a, b]:\n";
        
        std::cout << "a = ";
    while (!(std::cin >> a))
    {
        std::cout << "Invalid input for a. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    std::cout << "b = ";
    while (!(std::cin >> b))
    {
        std::cout << "Invalid input for b. Please enter a number: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
        if (a > b)
        {
            Swap(&a, &b);
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(a, b);

        for (int i = 0; i < n; i++)
        {
            *(arr + i) = dist(gen);
        }

        std::cout << "Array was filled with random numbers from [" << a << ", " << b << "]\n";
        break;
    }
    default:
        std::cout << "Invalid input\n";
        delete [] arr;
        return 1;
    }
    
    OutputOfArray(arr, n);

    int counter = Count(arr, n);

    std::cout << "Amount of different elements is: " << counter << std::endl;

    double sum = SumBetweenNegatives(arr, n);

    std::cout << "Sum between first and last negative elements is: " << sum << std::endl;

    double x;
    std::cout << "Enter number X: ";
    while (!(std::cin >> x))
    {
        std::cout << "Invalid input" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    int newArray = MakeArray(arr, n, x);
    
    std::cout << "Number of remaining elements: " << newArray << std::endl;
    std::cout << "Number of removed elements: " << n - newArray << std::endl;

    delete[] arr;
    
    return 0;
}

