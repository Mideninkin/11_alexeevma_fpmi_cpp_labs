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
    Vector();
    Vector(size_t vec_size);
    Vector(std::initializer_list<int> list);
    Vector(const Vector& other);
    Vector(int num, size_t vec_size);
    
    ~Vector();
    
    Vector& operator=(const Vector& other);
    const int& operator[](size_t index) const;
    int& operator[](size_t index);
    
    const int& At(size_t index) const;
    int& At(size_t index);
    size_t Size() const;
    size_t Capacity() const;

    Vector& PushBack(int element);
    Vector& PopBack();
    Vector& Clear();
    Vector& Reserve(size_t Capacity);
    void Swap(Vector& second);
    
    friend std::ostream& operator<<(std::ostream& outstr, const Vector& vector);
};
