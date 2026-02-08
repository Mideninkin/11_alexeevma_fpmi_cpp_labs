#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <limits>
#include <cmath>

void InputOfNumbersInVector(std::vector<int>& vector) {
    int number;
    
    std::cout << "Enter integer numbers (enter a non-number to stop entering):" 
    << std::endl;
    
    while (std::cin >> number) {
        vector.push_back(number);
    }
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << std::endl << "Final result (" << vector.size() << " numbers):"
    << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void SumOfVector(std::vector<int>& vector) {
    int sum = std::accumulate(vector.begin(), vector.end(), 0);
    std::cout << "Sum of numbers in vector is " << sum << "." << std::endl;
}

void AmountOfVectorNumbers(std::vector<int>& vector) {
    std::cout << "There are " << vector.size() << " numbers in vector in total." 
    << std::endl;
}

void AmountOfElementsEqualToValue(std::vector<int>& vector) {
    int value;
    std::cout << "Enter an integer value to compare with vector elements: " 
    << std::endl;
    std::cin >> value;
    
    size_t counter = std::count(vector.begin(), vector.end(), value);
    
    if (counter == 1)
        std::cout << counter << " of elements is equal to value." << std::endl;
    else if (counter > 1)
        std::cout << counter << " of elements are equal to value." << std::endl;
    else
        std::cout << "There are not elements equal to this value!" << std::endl;
}

void FindAmountOfBiggerThanValue(std::vector<int>& vector) {
    int value;
    std::cout << "Enter an integer value to compare with vector elements: " 
    << std::endl;
    std::cin >> value;
    
    size_t counter = std::count_if(vector.begin(), vector.end(), 
    [value](int x) { return x > value; });
    
    if (counter == 1)
        std::cout << counter << " of elements is bigger than value." << std::endl;
    else if (counter > 1)
        std::cout << counter << " of elements are bigger than value." << std::endl;
    else
        std::cout << "There are not elements bigger than this value!" << std::endl;
}

void ReplaceZerosWithArithmeticAverage(std::vector<int>& vector) {
    if (vector.empty()) return;
    
    int sum = std::accumulate(vector.begin(), vector.end(), 0);
    int average = sum / static_cast<int>(vector.size());
    
    std::replace_if(vector.begin(), vector.end(), 
    [](int x) { return x == 0; }, 
    average);

    std::cout << "Vector after replacing zeros with arithmetic average:"
    << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void AddVectorIntervalSumToSomeElement(std::vector<int>& vector) {
    int lower_border, higher_border;
    
    std::cout << "Enter a lower border of interval:" << std::endl;
    std::cin >> lower_border;
    std::cout << "Enter a higher border of interval:" << std::endl;
    std::cin >> higher_border;
    
    int sum = std::accumulate(vector.begin(), vector.end(), 0,
    [lower_border, higher_border](int result, int x) {
    return (x >= lower_border && x <= higher_border) ? result + x : result;
    });
    
    std::transform(vector.begin(), vector.end(), vector.begin(),
    [sum](int x) { return sum + x; });
    
    std::cout << "Modified vector (after adding interval sum to elements): " << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void ReplaceEvenModulesWithDiff (std::vector<int>& vector) {
    int min = vector[0];
    int max = vector[0];
    auto [minIt2, maxIt2] = std::minmax_element(vector.begin(), vector.end());
    int diff = *maxIt2 - *minIt2;
    std::transform(vector.begin(), vector.end(), vector.begin(),
    [diff](int x) { return (std::abs(x) % 2 == 0) ?  diff : x;});
    std::cout << "Modified vector (after replacing even modules with max - min):"
    << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

}

void DeleteEqualModulesExceptFirst (std::vector<int> vector) {
    if (vector.empty()) return;

    int module = vector[0];
    bool first_appear = false;
    
    auto it = std::remove_if(vector.begin(), vector.end(),
    [&first_appear, &module](int x) {
    if (x == module) {
        if (!first_appear) {
            first_appear = true;
            return false;
            }
        return true;
        }
    return false;
    });
    vector.erase(it, vector.end());
    std::cout << "Modified vector after deleting module-equal elements (except first):"
    << std::endl;
    for (int num : vector) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec;
    InputOfNumbersInVector(vec);
    SumOfVector(vec);
    AmountOfVectorNumbers(vec);
    AmountOfElementsEqualToValue(vec);
    FindAmountOfBiggerThanValue(vec);
    ReplaceZerosWithArithmeticAverage(vec);
    AddVectorIntervalSumToSomeElement(vec);
    ReplaceEvenModulesWithDiff(vec);
    DeleteEqualModulesExceptFirst(vec);
    
    return 0;
}

