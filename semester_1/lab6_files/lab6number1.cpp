#include <iostream>
#include <string>
#include <fstream>
#include <vector>
bool Is_EmptyFile(std::ifstream &file)
{
    return file.peek() == std::fstream::traits_type::eof();
}
bool Is_Open(std::ifstream &file)
{
    return file.is_open();
}

std::vector<std::string> WriteWordsToVector(const std::string filename)
{
    std::ifstream fin{filename};
    if (!fin.is_open())
    {
        throw std::string("Error in process of opening file.");
    }

    if (Is_EmptyFile(fin))
    {
        throw std::string("Your file is empty!");
    }

    std::vector<std::string> words;
    std::string word;
    while (fin >> word)
    {
        words.push_back(word);
    }
    fin.close();
    return words;
}

void PrintVector(const std::vector<std::string> &vec)
{
    std::cout << "Words from file are: " << std::endl;
    for (int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void FindMostPopularWorld(const std::vector<std::string> &vec)
{
    std::string PopularWord = vec[0];
    int MaxCounter = 0;
    bool IsTie = false;

    for (int i = 0; i < vec.size(); ++i)
    {
        int counter = 0;
        
        for (int j = 0; j < vec.size(); ++j)
        {
            if (vec[j] == vec[i])
            {
                counter++;
            }
        }
        
        if (counter > MaxCounter)
        {
            MaxCounter = counter;
            PopularWord = vec[i];
            bool IsTie = false;
        }
        else if (counter == MaxCounter && vec[i] != PopularWord)
        {
            IsTie = true;
        }
    }
    if (IsTie)
    {
        std::cout << "Several words have the same maximum frequency (" << MaxCounter << " times)" << std::endl;
    }
    else
    {
    std::cout << "Most popular word in file is: '" << PopularWord << "'." << std::endl;
    std::cout << "It appears " << MaxCounter << " times." << std::endl;
    }
}

int main()
{
    const std::string file("input.txt");
    try
    {
        std::vector<std::string> words = WriteWordsToVector(file);
        PrintVector(words);
        FindMostPopularWorld(words);
    }
    catch (const std::string &msg)
    {
        std::cerr << msg << std::endl;
    }
    return 0;
}
