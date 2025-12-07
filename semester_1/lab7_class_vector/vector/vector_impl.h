#pragma once
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <cstdint>
#include <stdexcept>

class Vector 
{
private: 
    size_t size_ = 0;
    size_t capacity_ = 0;
    int* arr_ = nullptr;
public:
Vector()
{
    std::cout << "Default constructor" << std::endl;
}

Vector(size_t vec_size):  size_{vec_size}, capacity_{size_}, 
arr_{new int [capacity_]}
{
    std::cout << "Filling zeros in vector" << std::endl;
    for (size_t k = 0; k < vec_size; ++k)
    {
        arr_[k] = 0;
    }
}

Vector(std::initializer_list<int> list) : size_{list.size()}, 
capacity_{size_}, arr_{new int [capacity_]}
{
    
    std::cout << "Initializer list" << std::endl;
    std::copy(list.begin(), list.end(), arr_);
}

Vector (const Vector& other) : size_{other.size_}, capacity_{other.capacity_}, 
arr_{new int [capacity_]}
{
    std::cout << "Copy constructor" << std::endl;
    std::copy (other.arr_, other.arr_ + size_, arr_);
}
Vector& operator=(const Vector& other)
{
    std::cout << "Operator=" << std::endl;
        
    if (this == &other) 
    {
        return *this;
    }
    
    delete [] arr_;
    
    size_ = other.size_;
    capacity_ = other.capacity_;
    arr_ = new int [capacity_];

    std::copy (other.arr_, other.arr_ + size_, arr_);
    return *this;
}

~Vector()
{
    std::cout << "Destructor" << std::endl;
    delete [] arr_;
}

void Swap(Vector& second)
{
    std::cout << "Method Swap" << std::endl;
    std::swap (size_, second.size_);
    std::swap (arr_, second.arr_);
    std::swap (capacity_, second.capacity_);
}

const int& operator[](size_t index) const
{
    std::cout << "Constant []" << std::endl;
    return arr_[index];
}

int& operator[](size_t index)
{
    std::cout << "Non-constant []" << std::endl;
    return arr_[index];
}
const int& At(size_t index) const
{
    std::cout << "Constant At" << std::endl;
    if(index >= size_)
    {
        throw std::out_of_range ("Index is out of range!");
    }
    return arr_[index];
}

int& At(size_t index)
{
    std::cout << "Non-constant At" << std::endl;
    if(index >= size_)
    {
        throw std::out_of_range ("Index is out of range!");
    }
    return arr_[index];
}

size_t Size() const
{
    std::cout << "Method Size" << std::endl;
    return size_;
}

size_t Capacity() const
{
    std::cout << "Method Capacity" << std::endl;
    return capacity_;
}

Vector& PushBack (int element)
{
    std::cout << "Method PushBack"<< std::endl ;
    if (capacity_ == size_)
    {
        size_t new_capacity;
        if(capacity_ == 0)
        {
            new_capacity = 1;
        }
        else
        {
            new_capacity = capacity_ * 2;
        }

        int* new_arr = new int [new_capacity];
        std::copy (arr_, arr_ + size_, new_arr);
        delete [] arr_;
        arr_ = new_arr;
        capacity_ = new_capacity;
    }

    arr_[size_] = element;
    size_++;

    return *this;
}

Vector& PopBack ()
{
    std::cout << "Method PopBack" << std::endl;
    if (size_ == 0)
    {
        std::cout << "There is nothing to delete!";
        return *this;
    }
    size_--;
    return *this;
}

Vector& Clear()
{
    std::cout << "Method Clear" << std::endl;
    size_ = 0;
    return *this;
}

Vector& Reserve(size_t Capacity)
{
    std::cout << "Method Reserve" << std::endl;
    if (capacity_ >= Capacity)
    return *this;
    
    int* Arr = new int[Capacity];
    for(size_t k = 0; k < size_; ++k)
    {
        Arr[k] = arr_[k];
    }

    delete [] arr_;
    arr_ = Arr;
    capacity_ = Capacity;
    return *this;
}
Vector(int num, size_t vec_size): size_{vec_size}, capacity_{size_},
arr_{new int [capacity_]}
{
    std::cout << "Filling in with numbers" << std::endl;
    for(size_t i = 0; i < vec_size; ++i)
    {
        arr_[i] = num;
    }
}
friend std::ostream& operator << (std::ostream& outstr, const Vector& vector);
};
