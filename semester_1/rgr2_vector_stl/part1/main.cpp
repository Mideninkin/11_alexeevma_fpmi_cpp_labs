#include <iostream>
#include <vector>
#include <limits>

void InputOfNumbersInVector (std::vector<int>& vector) {
int number;
std::cout << "Enter integer numbers: ";
while (std::cin >> number) {
vector.push_back(number);
if (!std::cin >> number) {       
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
}
}
int main() {
std::vector<int> vec;
InputOfNumbersInVector (vec);

return 0;
}