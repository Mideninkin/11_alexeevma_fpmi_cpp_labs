#include <iostream>

int main() 
{
    int number;
    std::cin >> number;
    int digit1 = number / 100000;         
    int digit2 = (number / 10000) % 10; 
    int digit3 = (number / 1000) % 10;     
    int digit4 = (number / 100) % 10; 
    int digit5 = (number / 10) % 10;  
    int digit6 = number % 10;
    
    int sum1 = digit1 + digit2 + digit3;
    
    int sum2 = digit4 + digit5 + digit6;
    
    if (sum1 == sum2)
    {
        std::cout << "Число " << number << " является счастливым!";
    } else {
        std::cout << "Число " << number << " не является счастливым.";
    }
       return 0;
}