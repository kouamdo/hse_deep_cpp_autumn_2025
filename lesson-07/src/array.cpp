#include "array.hpp"

template<class T, size_t Size>
T Array<T, Size>::get(size_t i)
{
    return data_[i];
}

template class Array<double, 100>;
template class Array<double, 10>;
template class Array<std::string, 25>;
