#include <iostream>
#include <ctime>
#include <random>
#include <limits>

void Input(int *x, int min)
{
    int d;
    while (!(std::cin >> d) || (d < min))
    {
        std::cout << "Invalid input" << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    *x = d;
}

void Swap(int *q, int *o)
{
    int temp = *q;
    *q = *o;
    *o = temp;
}

void OutputOfMatrix(int** arr, int n, int m)
{
    std::cout << "Matrix: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << *(*(arr + i) + j);
            if (j < m - 1)
                std::cout << "\t";
        }
        std::cout << std::endl;
    }
}
void AllocateMatrix(int**& arr, int n)
{
    arr = new int *[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];
}

void DecideTypeOfInput(int **arr, int n)
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
        std::cout << "Enter " << n * n << " integer numbers:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                std::cout << "Element [" << i << "][" << j << "]:";
                while (!(std::cin >> arr[i][j]))
                {
                    std::cout << "Invalid input" << '\n';
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }
        }
        break;
    }
    case 'A':
    case 'a':
    {
        std::cout << "Enter interval borders [a, b]:\n";

        std::cout << "a = ";
        while (!(std::cin >> a))
        {
            std::cout << "Invalid input for a. Please enter an integer number: " << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "b = ";
        while (!(std::cin >> b))
        {
            std::cout << "Invalid input for b. Please enter an integer number: " << std::endl;
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
            for (int j = 0; j < n; j++)
            {
                int random_number = a + std::rand() % (b - a + 1);
                *(*(arr + i) + j) = random_number;
            }
        }

        std::cout << "Matrix was filled with random numbers from [" << a << ", " << b << "]\n";
        break;
    }
    default:
        std::cout << "Invalid input. Using automatic fill." << std::endl;
        std::srand(std::time(0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                *(*(arr + i) + j) = -50 + std::rand() % 100;
            }
        }
    }
}

int main()

{
    const int max = 100;
    int n;

    std::cout << "Enter the side length of the square matrix: " << std::endl;
    Input(&n, , );
    std::cout << "Number of matrix elements: " << n * n << std::endl;

    int ** arr;
    AllocateMatrix(arr, n);

    DecideTypeOfInput(arr, n);
    OutputOfMatrix(arr, n);
    FindMaximumsInNegativeColumns(arr, n);
    FindNumberOfNegatives(arr, n);

    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
    return 0;
}