#include <iostream>

template<class T>
void foo(const T&& param)
{
    std::cout << "foo(univeral)" << std::endl;
    f(std::forward<T&&>(param));
}

template<class T>
void f(T& param)
{
    std::cout << "lvalue" << std::endl;
}

template<class T>
void f(const T&& param)
{
    std::cout << "rvalue" << std::endl;
}

class A
{
};

int main()
{
    A a;
    foo(a);
    foo(A{});
}
