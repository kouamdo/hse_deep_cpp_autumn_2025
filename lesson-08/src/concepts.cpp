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

std::ostream& operator<<(std::ostream& os, A a)
{
    os << "A()";
    return os;
}

template<class T>
concept HasVoidFoo =
    requires(std::ostream& os, T t) {
        { t.foo() } -> std::same_as<void>;
        { os << t } -> std::convertible_to<std::ostream&>;
    };

// Тип T имеет функцию void foo()
template<HasVoidFoo T>
void execute(T obj)
{
    obj.foo();
    std::cout << "execute::has_foo == true" << std::endl;
}

template<class T>
void execute(T obj)
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

