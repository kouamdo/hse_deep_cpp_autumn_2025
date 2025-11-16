#include <cstddef>
#include <cstdint>

template<class T, size_t n>
class Array
{
public:
    using iterator = size_t;
    static size_t const_iterator;
private:
    T data_[n];
};

template <class Container>
class Parser
{
    typename Container::iterator *x;
    //Container::const_iterator *y; // Ошибка!!! обращаемся к статическому полю
};

int main()
{
    Parser<Array<int32_t, 10>> parser;
}
