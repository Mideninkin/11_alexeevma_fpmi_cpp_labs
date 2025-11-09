#include <iostream>
#include <string>

void InputOfString (std::string& newstr)
{
std::cout << "Enter string: " << std::endl;
getline (std::cin, newstr);
if (newstr.empty())
        {
            throw "Error! Your string is empty";
        }

}

void Function(std::string& newstr)
{
    const std::string separators = " ,;:.\"!?'*\n";
    unsigned words_counter = 0;
    unsigned numbers_counter = 0;
    size_t longest_number = 0;
    std::string first_biggest_number;
    size_t shortest_number = SIZE_MAX;
    std::string last_smallest_number;
    size_t longest_start = 0, longest_end = 0;
    size_t shortest_start = 0, shortest_end = 0;
    std::string longest_number_str, shortest_number_str;
    size_t start = newstr.find_first_not_of(separators);
    while (start != std::string::npos)
    {
        words_counter++;
        size_t end = newstr.find_first_of(separators, start + 1);
        if (end == std::string::npos) 
        {
            end = newstr.length();
        }
        bool Is_number = true;
        for (size_t i = start; i < end; i++)
        {
            if (!isdigit(newstr[i]))
            {
                Is_number = false;
                break;
            }
        }
        if (Is_number)
        {
            numbers_counter++;
            std::string current_number = newstr.substr(start, end - start);
            size_t current_length = current_number.length();
            std::cout << current_number << " ";
            if (current_length > longest_number)
            {
                longest_number = current_length;
                first_biggest_number = current_number;
                longest_start = start;
                longest_end = end;
            }
            if (current_length <= shortest_number)
            {
                shortest_number = current_length;
                last_smallest_number = current_number;
                shortest_start = start;
                shortest_end = end;
            }
        }
        start = newstr.find_first_not_of(separators, end + 1);
    }
    std::cout << std::endl;
    std::cout << "Text contains " << words_counter << " words." << std::endl;
    std::cout << numbers_counter << " of them are numbers." << std::endl;
    if (!numbers_counter)
    {
        throw "No numbers found in your string!";
    }
    if (longest_number == 0 ^ shortest_number == SIZE_MAX)
    {
        throw "There is only one number in your string!";
    }
    else
    {
    std::cout << "First longest number is " << first_biggest_number << std::endl;
    std::cout << "Length of this number is "<< longest_number << std::endl;
    std::cout << "Last smallest number is " << last_smallest_number << std::endl;
    std::cout << "Length of this number is "<< shortest_number << std::endl;
    
    std::string result_str = newstr;
    result_str.replace(longest_start, longest_end - longest_start, shortest_number_str);
    result_str.replace(shortest_start, shortest_end - shortest_start, longest_number_str);
        
        std::cout << "Original string: " << newstr << std::endl;
        std::cout << "Modified string: " << result_str << std::endl;
    }
}
int main()
{
    try
    {    
    std::string newstr;
    InputOfString (newstr);
    Function (newstr);
    }
    catch(const char* msg)
    {
        std::cerr << msg;
    }
    return 0;
}