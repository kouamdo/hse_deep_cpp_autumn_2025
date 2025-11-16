#include <iostream>

template <class T>
void print(T&& val)
{
    std::cout << val << '\n';
}

template <class T, class... Args>
void print(T&& val, Args&&... args)
{
    std::cout << val << ' ';
    print(std::forward<Args>(args)...);
}

template<class... Args>
void print2(Args&&... args)
{
    (std::cout << ... << args) << '\n';
}

int main()
{
    print(1, "abc", 2.5);
    print2(1, "abc", 2.5);
    return 0;
}

