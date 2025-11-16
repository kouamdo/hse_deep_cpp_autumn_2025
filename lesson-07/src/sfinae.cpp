#include <iostream>
#include <type_traits>
struct A
{
    void foo()
    {
        std::cout << "A::foo" << std::endl;
    }
};

struct B
{
    void foo()
    {
        std::cout << "B::foo" << std::endl;
    }
};

struct C
{
    void foo(int a)
    {
        std::cout << "C::foo" << std::endl;
    }
};

template<class T1, class T2>
struct is_same
{
    static const bool value = false;
};

template<class T>
struct is_same<T, T>
{
    static const bool value = true;
};

template<class T>
struct has_foo
{
    static const bool value = is_same<void, decltype(has_foo<T>::check(static_cast<T*>(nullptr)))>::value;

    static int check(...);

    template<class U>
    static auto check(U *u) -> decltype(u->foo());
};

// Тип T имеет функцию void foo()
template<class T>
void execute(T obj,
             typename std::enable_if<has_foo<T>::value>::type* = nullptr)
{
    obj.foo();
    std::cout << "execute::has_foo == true" << std::endl;
}

template<class T>
void execute(T obj,
             typename std::enable_if<!has_foo<T>::value>::type* = nullptr)
{
    // какая-то сложная логика расчёта
    // ...
    std::cout << "execute::has_foo == false" << std::endl;
}

int main()
{
    {
        A a;
        execute(a);
    }
    {
        B b;
        execute(b);
    }
    {
        C c;
        execute(c);
    }
    {
        std::string str;
        execute(str);
    }
    return 0;
}

