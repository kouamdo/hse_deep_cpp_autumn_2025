#include <iostream>

#include "common.hpp"


struct Foo
{
    using iterator = int;
    static const int iterator2 = 10;
};


/*
 * int square(int num)....
 */

void foo(Foo::iterator it)
{
}

struct Boo
{
    typename Foo::iterator it;
};

int main()
{
    solution();
    std::cout << Foo::iterator2 << std::endl;
    Foo::iterator it;
    foo(20);
    Boo boo;
    return square(4);
}
