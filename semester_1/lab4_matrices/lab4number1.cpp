#include <iostream>
#include <ctime>
#include <random>
#include <climits>

void Input(int& n, int min)
{
    int d;
    if (!(std::cin >> d) || (d < min))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw "Error. Number must be an integer\n";
    }
    n = d;
}

void OutputOfMatrix(int **matrix, int n)
{
    std::cout << "Matrix: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << *(*(matrix + i) + j);
            if (j < n - 1)
                std::cout << "\t";
        }
        std::cout << std::endl;
    }
}
void AllocateMatrix(int **&matrix, int n)
{
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[n];
}

void FindMaximumsInNegativeColumns(int **matrix, int n)
{
    bool FoundColumnWithoutPositives = false;
    bool headerPrinted = false;
    for (int j = 0; j < n; j++)
    {
        bool HasPositive = false;

        for (int i = 0; i < n; i++)
        {
            if (*(*(matrix + i) + j) > 0)
            {
                HasPositive = true;
                break;
            }
        }
        
        if (!HasPositive)
        {
            FoundColumnWithoutPositives = true; 
            if (!headerPrinted)
            {
                std::cout << "Maximums in columns without positive elements: " << std::endl;
                headerPrinted = true;
            }
            int max = matrix[0][j];
            for (int i = 0; i < n; i++)
            {
                if (matrix[i][j] > max)
                    max = matrix[i][j];
            }
            std::cout << "Column " << j + 1 << ": " << max << std::endl;
        }
    }
    if (!FoundColumnWithoutPositives)
        {
            throw "There are no columns without positive elements!\n";
        }
    
}

void FindNumberOfNegatives(int **matrix, int n)
{
    int counter = 0;
    for (int j = n - 1; j >= 0; j--)
    {
        for (int i = 0; i < n; i++)
        {
            if (matrix[i][j] < 0 && i + j >= n - 1)
                counter += 1;
        }
    }
    std::cout << "Number of negative elements in lower right triangle: " << counter;
}

void CleanDinamicMemory(int** matrix, int n)
    {
    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
    }

void DecideTypeOfInput(int **matrix, int n)
{
    char answer;
    std::cout << "What input do you choose: manual or automatic? Press 'M' or 'm' to choose 1 option, 'A' or 'a' to choose 2 option: ";
    if (!(std::cin >> answer)) 
    {
        throw "Error. Input must be a char\n";
    }

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
                Input(matrix[i][j], INT_MIN);
            }
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
            for (int j = 0; j < n; j++)
            {
                int random_number = a + std::rand() % (b - a + 1);
                *(*(matrix + i) + j) = random_number;
            }
        }

        std::cout << "Matrix was filled with random numbers from [" << a << ", " << b << "]\n";
        break;
    }
    default:
        CleanDinamicMemory(matrix, n);
        throw "Error! Enter a char('A', 'a' or 'M', 'm')\n";
    }
}

int main()

{
    int n;
    try
    {
    std::cout << "Enter the side length of the square matrix: " << std::endl;
    Input(n, 1);
    std::cout << "Number of matrix elements: " << n * n << std::endl;

    int **matrix;
    AllocateMatrix(matrix, n);
    DecideTypeOfInput(matrix, n);
    OutputOfMatrix(matrix, n);
    FindMaximumsInNegativeColumns(matrix, n);
    FindNumberOfNegatives(matrix, n);
    CleanDinamicMemory(matrix, n);
    }
    
    catch(const char* msg)
    {
        std::cerr << msg;
    }
    return 0;
}
