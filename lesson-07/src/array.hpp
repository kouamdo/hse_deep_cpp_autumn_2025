#include <iostream>

template<class T, size_t Size>
class Array
{
public:
    T get(size_t i);
private:
    T data_[Size];
};

#include "array.tpp"
