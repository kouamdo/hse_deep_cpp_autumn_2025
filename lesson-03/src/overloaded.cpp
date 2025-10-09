#include <iostream>

void foo(int&)
{
    std::cout << "foo(int &)" << std::endl;
}

/*void foo(int)
{
    std::cout << "foo(int)" << std::endl;
}*/
/*
double foo(int)
{
}
*/

void foo(const int&)
{
    std::cout << "foo(const int &)" << std::endl;
}

void foo(int&&)
{
    std::cout << "foo(&&)" << std::endl;
}

void boo(const std::string& str)
{
}


void boo(int&&)
{
    std::cout << "boo(&&)" << std::endl;
}

void boo(int&)
{
    std::cout << "boo(&)" << std::endl;
}

int main()
{
    boo("hello");
    foo(10);
    int a = 15;
    //foo(a);
    boo(a);
    boo(15);
    boo(std::move(a));
}
