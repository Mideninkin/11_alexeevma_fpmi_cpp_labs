#include <set>
#include <iostream>
#include <cstdint>
#include <limits>

std::set<int> FindPrimeNumbers() {
    std::set<int> numbers_set;
    int N;
    while (true) {
        std::cout << "Enter N to find prime numbers in values from 2 to N" << std::endl;
        std::cin >> N;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a valid integer number." << std::endl;
        }
        else if (N < 2) {
            std::cout << "N must be greater than or equal to 2. Please try again." << std::endl;
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    for (size_t i = 2; i <= N; i++) {    
        numbers_set.insert(i);
    }
    for (size_t i = 2; i * i <= N; i++) {
        if (numbers_set.find(i) != numbers_set.end()) {
            for (size_t k = i * i; k <= N; k += i) {
                numbers_set.erase(k);
            }
        }
    } 

    for (int n: numbers_set) {
        std::cout << n << " ";
    }
    std::cout << "are prime numbers in interval from 2 to " << N << "." << std::endl;
    return numbers_set;
}

int main() {
    std::set<int> primes = FindPrimeNumbers();
    
    return 0;
}
