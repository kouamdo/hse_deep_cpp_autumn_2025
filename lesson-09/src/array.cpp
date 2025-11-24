#include <iostream>
#include <array>

template<class T, size_t N>
class array
{
public:
    using size_type = size_t;
    using value_type = T;
    using iterator = int;
public:
    array(std::initializer_list<T> list) : size_(N)
    {
        auto it = std::begin(list);
        for(size_t i = 0; it != std::end(list); ++i, ++it)
        {
            data_[i] = *it;
        }
    }

    const T& operator[](size_type i) const
    {
        return data_[i];
    }

    size_type size() const
    {
        return size_;
    }
private:
    T data_[N];
    size_t size_{0};
};

int main()
{
    array<int32_t, 5> arr = {1, 5, 3, 2, 6};
    std::cout << arr[2] << std::endl;
    array<int32_t, 5>::iterator it = 10;

    std::array<int32_t, 5> arr2 = {1,2,3,4,5};
    //std::cout << arr2[5] << std::endl;
    //std::cout << arr2.at(5) << std::endl;

    int32_t* ptr = arr2.data();
    std::cout << *ptr << std::endl;
    std::cout << *(ptr+2) << std::endl;
}
