#include <iostream>
#include <ctime>
#include <random>

void Input(int *x, int min, int max)
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

void Swap(int *q, int *o)
{
    int temp = *q;
    *q = *o;
    *o = temp;
}

void OutputOfMatrix(int **arr, int n)
{
    std::cout << "Matrix: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << *(*(arr + i) + j);
            if (j < n - 1)
                std::cout << "\t";
        }
        std::cout << std::endl;
    }
}

void FindMaximumsInNegativeColumns(int **arr, int n)
{
    std::cout << "Maximums in columns without positive elements: " << std::endl;
    for (int j = 0; j < n; j++)
    {
        bool HasPositive = false;

        for (int i = 0; i < n; i++)
        {
            if (*(*(arr + i) + j) > 0)
            {
                HasPositive = true;
                break;
            }
        }

        if (!HasPositive)
        {
            int max = arr[0][j];
            for (int i = 0; i < n; i++)
            {
                if (arr[i][j] > max)
                    max = arr[i][j];
            }
            std::cout << "Column: " << j + 1 << ": " << max << std::endl;
        }
    }
}

void FindNumberOfNegatives(int **arr, int n)
{
    int counter = 0;
    for (int j = n - 1; j >= 0; j--)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i][j] < 0 && i + j >= n - 1)
                counter += 1;
        }
    }
    std::cout << "Number of negative elements in lower right triangle: " << counter;
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
    int n, i, j;

    std::cout << "Enter the side length of the square matrix (1-100): " << std::endl;
    Input(&n, 1, 100);
    std::cout << "Number of matrix elements: " << n * n << std::endl;

    int **arr = new int *[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[n];

    DecideTypeOfInput(arr, n);
    OutputOfMatrix(arr, n);
    FindMaximumsInNegativeColumns(arr, n);
    FindNumberOfNegatives(arr, n);

    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
    return 0;
}