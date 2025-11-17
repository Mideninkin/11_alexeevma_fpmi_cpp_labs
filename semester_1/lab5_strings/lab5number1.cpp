#include <iostream>
#include <string>
#include <climits>
#include <vector>

void InputOfString (std::string& original_string)
{
std::cout << "Enter string: " << std::endl;
getline (std::cin, original_string);
if (original_string.empty())
        {
            throw "Error! Your string is empty";
        }

}

void Function(std::string& original_string)
{
    const std::string separators = " ,;:.\"!?'*\n";
    unsigned words_counter = 0;
    unsigned numbers_counter = 0;
    std::vector<std::string> numbers;
    std::vector<size_t> start_positions;
    std::vector<size_t> end_positions;
    size_t start = original_string.find_first_not_of(separators);
    while (start != std::string::npos)
    {
        words_counter++;
        size_t end = original_string.find_first_of(separators, start + 1);
        if (end == std::string::npos) 
        {
            end = original_string.length();
        }
        bool Is_number = true;
        for (size_t i = start; i < end; i++)
        {
            if (!isdigit(original_string[i]))
            {
                Is_number = false;
                break;
            }
        }
        if (Is_number)
        {
            numbers_counter++;
            std::string current_number = original_string.substr(start, end - start);
            numbers.push_back(current_number);
            start_positions.push_back(start);
            end_positions.push_back(end);
            std::cout << current_number << " ";
        }
        start = original_string.find_first_not_of(separators, end + 1);
    }
    std::cout << std::endl;
    std::cout << "Text contains " << words_counter << " words." << std::endl;
    std::cout << numbers_counter << " of them are numbers." << std::endl;
    if (!numbers_counter)
    {
        throw "No numbers found in your string!";
    }
    if (numbers_counter == 1)
    {
        throw "There is only one number in your string!";
    }
    size_t longest_index = 0;
    size_t shortest_index = 0;
    size_t longest_length = numbers[0].length();
    size_t shortest_length = numbers[0].length();
    
    for (size_t i = 1; i < numbers.size(); i++) 
    {
        if (numbers[i].length() > longest_length) 
        {
            longest_length = numbers[i].length();
            longest_index = i;
        }
        if (numbers[i].length() <= shortest_length) 
        {
            shortest_length = numbers[i].length();
            shortest_index = i;
        }
    }
    std::cout << "First longest number is " << numbers[longest_index] << std::endl;
    std::cout << "Length of this number is "<< longest_length << std::endl;
    std::cout << "Last smallest number is " << numbers[shortest_index] << std::endl;
    std::cout << "Length of this number is "<< shortest_length << std::endl;
    
    std::string new_str = original_string;

    if (start_positions[longest_index] < start_positions[shortest_index]) 
    {
        new_str.erase(start_positions[longest_index], numbers[longest_index].length());
        new_str.insert(start_positions[longest_index], numbers[shortest_index]);
        size_t new_shortest_pos = start_positions[shortest_index] + (numbers[shortest_index].length() - numbers[longest_index].length());
        new_str.erase(new_shortest_pos, numbers[shortest_index].length());
        new_str.insert(new_shortest_pos, numbers[longest_index]);
    }
    else
    {
        new_str.erase(start_positions[shortest_index], numbers[shortest_index].length());
        new_str.insert(start_positions[shortest_index], numbers[longest_index]);
        size_t new_longest_pos = start_positions[longest_index] + (numbers[longest_index].length() - numbers[shortest_index].length());
        new_str.erase(new_longest_pos, numbers[longest_index].length());
        new_str.insert(new_longest_pos, numbers[shortest_index]);
    }    
        std::cout << "Original string: " << original_string << std::endl;
        std::cout << "Modified string: " << new_str << std::endl;
}
int main()
{
    try
    {    
    std::string original_string;
    InputOfString (original_string);
    Function (original_string);
    }
    catch(const char* msg)
    {
        std::cerr << msg;
    }
    return 0;
}