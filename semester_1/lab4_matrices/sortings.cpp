#include <iostream>
#include <ctime>
#include <random>
#include <limits>

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

void OutputOfMatrix(int **matrix, int n, int m)
{
    std::cout << "Matrix: " << std::endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << *(*(matrix + i) + j);
            if (j < m - 1)
                std::cout << "\t";
        }
        std::cout << std::endl;
    }
}
void AllocateMatrix(int **&matrix, int n, int m)
{
    matrix = new int *[n];
    for (int i = 0; i < n; i++)
        matrix[i] = new int[m];
}

void DecideTypeOfInput(int **matrix, int n, int m)
{
    char answer;
    std::cout << "What input do you choose: manual or automatic? Press 'M' or 'm' to choose 1 option, 'A' or 'a' to choose 2 option: ";
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
            for (int j = 0; j < m; j++)
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
            for (int j = 0; j < m; j++)
            {
                int random_number = a + std::rand() % (b - a + 1);
                *(*(matrix + i) + j) = random_number;
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
                *(*(matrix + i) + j) = -50 + std::rand() % 100;
            }
        }
    }
}

void CountingSort(int **matrix, int n, int m, bool ascending)
{
    int size = n * m;
    int *count = new int[size]();

    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            int i_row = i / m, i_col = i % m;
            int j_row = j / m, j_col = j % m;

            if (matrix[i_row][i_col] < matrix[j_row][j_col])
                count[j]++;
            else
                count[i]++;
        }
    }
    int **tempMatrix = new int *[n];
    for (int i = 0; i < n; i++)
        tempMatrix[i] = new int[m];
    for (int i = 0; i < size; i++)
    {
        int orig_row = i / m, orig_col = i % m;
        int new_pos = ascending ? count[i] : (size - 1 - count[i]);
        int new_row = new_pos / m, new_col = new_pos % m;
        tempMatrix[new_row][new_col] = matrix[orig_row][orig_col];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = tempMatrix[i][j];
        }
        delete[] tempMatrix[i];
    }
    delete[] tempMatrix;
    delete[] count;
}

void InsertionSort(int **matrix, int n, int m, bool ascending)
{
    int size = n * m;

    for (int k = 1; k < size; k++)
    {
        int i_row = k / m, i_col = k % m;
        int x = matrix[i_row][i_col];

        int j = k - 1;

        while (j >= 0)
        {
            int j_row = j / m, j_col = j % m;
            int j1_row = (j + 1) / m, j1_col = (j + 1) % m;

            bool condition = ascending ? (matrix[j_row][j_col] > x) : (matrix[j_row][j_col] < x);

            if (condition)
            {
                matrix[j1_row][j1_col] = matrix[j_row][j_col];
                j--;
            }
            else
            {
                break;
            }
        }
        int new_row = (j + 1) / m, new_col = (j + 1) % m;
        matrix[new_row][new_col] = x;
    }
}

void BubbleSort(int **matrix, int n, int m, bool ascending)
{
    int size = n * m;

    for (int i = 0; i < size; i++)
    {
        for (int j = size - 1; j > i; j--)
        {
            int j_row = j / m, j_col = j % m;
            int j1_row = (j - 1) / m, j1_col = (j - 1) % m;

            bool condition = ascending ? (matrix[j1_row][j1_col] > matrix[j_row][j_col]) : (matrix[j1_row][j1_col] < matrix[j_row][j_col]);

            if (condition)
            {
                std::swap(matrix[j1_row][j1_col], matrix[j_row][j_col]);
            }
        }
    }
}
void merge(int **matrix, int left, int mid, int right, int m, int* temp, bool ascending)
{
    int i = left;
    int j = mid;
    int k = left;

    while (i < mid && j < right)
    {
        int i_row = i / m, i_col = i % m;
        int j_row = j / m, j_col = j % m;
        
        if ((ascending && matrix[i_row][i_col] <= matrix[j_row][j_col]) || (!ascending && matrix[i_row][i_col] >= matrix[j_row][j_col]))
        {
            temp[k] = matrix[i_row][i_col];
            i++;
        }
        else
        {
            temp[k] = matrix[j_row][j_col];
            j++;
        }
        k++;
    }
    
    while (i < mid)
    {
        int i_row = i / m, i_col = i % m;
        temp[k] = matrix[i_row][i_col];
        i++;
        k++;
    }
    
    while (j < right)
    {
        int j_row = j / m, j_col = j % m;
        temp[k] = matrix[j_row][j_col];
        j++;
        k++;
    }

    for (int t = left; t < right; t++)
    {
        int row = t / m;
        int col = t % m;
        matrix[row][col] = temp[t];
    }
}

void mergeSort(int **matrix, int left, int right, int m, int* temp, bool ascending)
{
    if (right - left <= 1) return;

    int mid = (left + right) / 2;

    mergeSort(matrix, left, mid, m, temp, ascending);
    mergeSort(matrix, mid, right, m, temp, ascending);

    merge(matrix, left, mid, right, m, temp, ascending);
}

void MergeSort(int **matrix, int n, int m, bool ascending)
{
    int size = n * m;
    int* temp = new int[size];
    mergeSort(matrix, 0, size, m, temp, ascending);
    delete[] temp;
}

void DecideTypeOfSorting(int **matrix, int n, int m)
{
    int algorithmChoice;
    char orderChoice;

    std::cout << "Choose sorting algorithm:\n";
    std::cout << "1 - Counting Sort\n";
    std::cout << "2 - Insertion Sort\n";
    std::cout << "3 - Bubble Sort\n";
    std::cout << "4 - Merge Sort\n";
    std::cout << "Enter your choice (1-4): " << std::endl;
    Input(algorithmChoice, 1);

    std::cout << "Choose sorting order:\n";
    std::cout << "A - Ascending (from smallest to largest)\n";
    std::cout << "D - Descending (from largest to smallest)\n";
    std::cout << "Enter your choice (A or D): ";
    std::cin >> orderChoice;

    bool ascending = (orderChoice == 'A' || orderChoice == 'a');

    std::cout << "Matrix before sorting:" << std::endl;
    OutputOfMatrix(matrix, n, m);

    switch (algorithmChoice)
    {
    case 1:
        std::cout << "\nUsing Counting Sort (" << (ascending ? "Ascending" : "Descending") << ")..." << std::endl;
        CountingSort(matrix, n, m, ascending);
        break;
    case 2:
        std::cout << "\nUsing Insertion Sort (" << (ascending ? "Ascending" : "Descending") << ")..." << std::endl;
        InsertionSort(matrix, n, m, ascending);
        break;
    case 3:
        std::cout << "\nUsing Bubble Sort (" << (ascending ? "Ascending" : "Descending") << ")..." << std::endl;
        BubbleSort(matrix, n, m, ascending);
        break;
    case 4:
        std::cout << "\nUsing Merge Sort (" << (ascending ? "Ascending" : "Descending") << ")..." << std::endl;
        MergeSort(matrix, n, m, ascending);
        break;
    default:
        std::cout << "\nInvalid choice. Using Insertion Sort (Ascending) by default." << std::endl;
        InsertionSort(matrix, n, m, true);
    }

    std::cout << "\nAfter sorting:" << std::endl;
    OutputOfMatrix(matrix, n, m);
}
int main()

{
    int n, m;

    std::cout << "Enter the length of the matrix: " << std::endl;
    Input(m, 1);
    std::cout << "Enter the width of the matrix: " << std::endl;
    Input(n, 1);
    std::cout << "Number of matrix elements: " << m * n << std::endl;

    int **matrix;
    AllocateMatrix(matrix, n, m);

    DecideTypeOfInput(matrix, n, m);
    OutputOfMatrix(matrix, n, m);

    DecideTypeOfSorting(matrix, n, m);

    for (int i = 0; i < n; i++)
        delete[] matrix[i];
    delete[] matrix;
    return 0;
}
