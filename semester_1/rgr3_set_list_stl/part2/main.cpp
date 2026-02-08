#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

struct Author {
    std::string surname;
    std::string name;
    std::string father_name;
    
    Author() = default;
    
    Author(const std::string& s, const std::string& n, const std::string& f)
        : surname(s), name(n), father_name(f) {}
    
    bool operator<(const Author& other) const {
        return surname < other.surname;
    }
    
    bool operator==(const Author& other) const {
        return surname == other.surname && 
               name == other.name && 
               father_name == other.father_name;
    }
    
    static Author ObjectfromString(const std::string& str) {
        std::istringstream iss(str);
        Author author;
        iss >> author.surname >> author.name >> author.father_name;
        return author;
    }
};

struct Book {
    int udc;
    std::list<Author> authors;
    std::string title;
    std::string year;
    
    bool operator<(const Book& other) const {
        return title < other.title;
    }
    
    bool HasAuthor(const std::string& surname) const {
        for (const auto& author : authors) {
            if (author.surname == surname) return true;
        }
        return false;
    }
    
    void Print() const {
        std::cout << "\nTitle: " << title;
        std::cout << "\nUDC: " << udc;
        std::cout << "\nYear: " << year;
        std::cout << "\nAuthors: ";
        for (const auto& author : authors) {
            std::cout << author.surname;
            if (!author.name.empty()) {
                std::cout << " " << author.name[0] << ".";
                if (!author.father_name.empty()) {
                    std::cout << " " << author.father_name[0] << ".";
                }
            }
            std::cout << "; ";
        }
        std::cout << "\n";
    }
};

class Library {
private:
    std::list<Book> books;
    
    std::list<Book>::iterator FindBook(const std::string& title) {
        return std::find_if(books.begin(), books.end(),
        [&title](const Book& b) { return b.title == title; });
    }
    
    void SortAll() {
        books.sort();
        for (auto& book : books) {
            book.authors.sort();
        }
    }

public:
    void ReadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cout << "Error in opening the file" << std::endl;
            return;
        }
        
        std::string line;
        Book current_book;
        
        while (std::getline(file, line)) {
            line.erase(0, line.find_first_not_of(" \t"));
            line.erase(line.find_last_not_of(" \t") + 1);
            
            if (line.empty()) {
                if (!current_book.title.empty()) {
                    books.push_back(current_book);
                    current_book = Book();
                }
                continue;
            }
            
            if (line.find("UDC:") == 0) {
                std::string udc_str = line.substr(4);
                udc_str.erase(0, udc_str.find_first_not_of(" \t"));
                current_book.udc = std::stoi(udc_str);
            }
            else if (line.find("Title:") == 0) {
                current_book.title = line.substr(6);
                current_book.title.erase(0, current_book.title.find_first_not_of(" \t"));
            }
            else if (line.find("Year:") == 0) {
                current_book.year = line.substr(5);
                current_book.year.erase(0, current_book.year.find_first_not_of(" \t"));
            }
            else if (line.find("Authors:") == 0) {
                std::string authorsStr = line.substr(8);
                std::istringstream iss(authorsStr);
                std::string authorToken;
                
                while (std::getline(iss, authorToken, ';')) {
                    authorToken.erase(0, authorToken.find_first_not_of(" \t"));
                    authorToken.erase(authorToken.find_last_not_of(" \t") + 1);
                    if (!authorToken.empty()) {
                        current_book.authors.push_back(Author::ObjectfromString(authorToken));
                    }
                }
            }
        }
        
        if (!current_book.title.empty()) {
            books.push_back(current_book);
        }
        
        file.close();
        SortAll();
        std::cout << "Loaded: " << books.size() << " books" << std::endl;
    }
    
    void SaveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (!file) {
            std::cout << "Error creating file" << std::endl;
            return;
        }
        
        for (const auto& book : books) {
            file << "UDC: " << book.udc << "\n";
            file << "Title: " << book.title << "\n";
            file << "Year: " << book.year << "\n";
            file << "Authors: ";
            
            bool first = true;
            for (const auto& author : book.authors) {
                if (!first) file << "; ";
                file << author.surname << " " << author.name << " " << author.father_name;
                first = false;
            }
            file << "\n\n";
        }
        
        file.close();
        std::cout << books.size() << " books were saved to " << filename << "\n";
    }
    
    void AddBook(const Book& book) {
        if (FindBook(book.title) != books.end()) {
            std::cout << "This book already exists\n";
            return;
        }
        
        books.push_back(book);
        SortAll();
        std::cout << "Book '" << book.title << "' was added\n";
    }
    
    void DeleteBook(const std::string& title) {
        auto it = FindBook(title);
        if (it == books.end()) {
            std::cout << "Library doesn't have this book: " << title << "\n";
            return;
        }
        
        books.erase(it);
        std::cout << "Book '" << title << "' was deleted\n";
    }
    
    void FindBooksByAuthor(const std::string& surname) {
        std::cout << "\nBooks by author '" << surname << "':\n";
        bool found = false;
        
        for (const auto& book : books) {
            if (book.HasAuthor(surname)) {
                book.Print();
                found = true;
            }
        }
        
        if (!found) std::cout << "No books found\n";
    }
    
    void AddAuthorToBook(const std::string& title, const Author& author) {
        auto it = FindBook(title);
        if (it == books.end()) {
            std::cout << "Book '" << title << "' doesn't exist\n";
            return;
        }
        
        it->authors.push_back(author);
        it->authors.sort();
        std::cout << "Author '" << author.surname << "' added to book '" << title << "'\n";
    }
    
    void RemoveAuthorFromBook(const std::string& title, const std::string& surname) {
        auto it = FindBook(title);
        if (it == books.end()) {
            std::cout << "Book '" << title << "' not found\n";
            return;
        }
        
        int oldSize = it->authors.size();
        it->authors.remove_if([&surname](const Author& a) { return a.surname == surname; });
        
        if (it->authors.size() < oldSize) {
            std::cout << "Author '" << surname << "' was deleted from book '" << title << "'\n";
        } else {
            std::cout << "Author '" << surname << "' not found in book '" << title << "'\n";
        }
    }
    
    void PrintAll() {
        if (books.empty()) {
            std::cout << "No books in the library\n";
            return;
        }
        
        std::cout << books.size() << " books are in the library";
        int i = 1;
        for (const auto& book : books) {
            std::cout << "\nBook №" << i++ << ":";
            book.Print();
        }
    }
};

int main() {
    std::ofstream test_file("books.txt");
    if (test_file) {
        test_file << "UDC: 4757\n";
        test_file << "Title: 1984\n";
        test_file << "Year: 1949\n";
        test_file << "Authors: Orwell George\n\n";
        
        test_file << "UDC: 5875\n";
        test_file << "Title: The Great Gatsby\n";
        test_file << "Year: 1925\n";
        test_file << "Authors: Fitzgerald F. Scott\n\n";
        
        test_file << "UDC: 7889\n";
        test_file << "Title: Harry Potter and the Philosopher's Stone\n";
        test_file << "Year: 1997\n";
        test_file << "Authors: Rowling J. K.\n";
        test_file.close();
    }

    Library lib;
    lib.ReadFromFile("books.txt");
    
    lib.PrintAll();
    
    lib.FindBooksByAuthor("Rowling");
    
    lib.AddAuthorToBook("Harry Potter and the Philosopher's Stone", 
    Author("Dostoevskiy", "Fiodor", "Mihaylovich"));
    
    lib.RemoveAuthorFromBook("Harry Potter and the Philosopher's Stone", "Dostoevskiy");
    
    Book new_book{123, {Author("Smith", "John", "A.")}, "Grey land", "2022"};
    lib.AddBook(new_book);

    lib.DeleteBook("1984");
    
    std::cout << "Final catalogue: ";
    lib.PrintAll();
    
    lib.SaveToFile("new_books.txt");
    
    return 0;
}
