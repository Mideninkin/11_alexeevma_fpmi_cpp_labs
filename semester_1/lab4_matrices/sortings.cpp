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
void AllocateMatrix(int**& arr, int n, int m)
{
    arr = new int *[n];
    for (int i = 0; i < n; i++)
        arr[i] = new int[m];
}

void DecideTypeOfInput(int **arr, int n, int m)
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
        std::cout << "Enter " << n * m << " integer numbers:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
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
            for (int j = 0; j < m; j++)
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

    void Merge(int** arr, int n, int m)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    if (arr[i][j] < arr[i][j + 1])
                    Swap(&arr[i][j]; &arr[i][j + 1]);
                }
                std::cout << arr[i][j];
            }
        }
    
    void DecideTypeOfSorting(int** arr, int n, int m)
{
    char option;
    std::cout << "What sorting do you prefer: MergingSort, ShellSort or ShakerSort? ";
    std::cin >> option;
    int a, b;
    switch (option)
    {
        case 'MergingSort':
        Merge(arr, n, m);
    }
}






int main()

{
    int n, m;

    std::cout << "Enter the side length of the matrix: " << std::endl;
    Input(&n, 1);
    Input(&m, 1);
    std::cout << "Number of matrix elements: " << n * n << std::endl;

    int ** arr;
    AllocateMatrix(arr, n, m);

    DecideTypeOfInput(arr, n, m);
    OutputOfMatrix(arr, n, m);
    DecideTypeOfSorting(arr, n, m);
    


    for (int i = 0; i < n; i++)
        delete[] arr[i];
    delete[] arr;
    return 0;
}
