#include <functional>
#include <iostream>
#include <vector>

using MoveFunction = std::function<void (int& x, int& y)>;

void moveLeft(int &x, int &y)
{
    std::cout << "moveLeft" << std::endl;
}

struct Functor
{
    void operator()(int&x, int&y)
    {
        std::cout << "Functor::operator()" << std::endl;
    }
};

int main()
{
    std::vector<MoveFunction> trajectory =
    {
        [](int& x, int& y) { std::cout << "lambda" << std::endl; },
        moveLeft,
        Functor{}
    };

    int a = 10, b = 20;
    for (auto move : trajectory)
    {
        move(a, b);
    }
}
