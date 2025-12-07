#include <iostream>

class A
{
public:
    A() : data_(new int[1024])
    {
        std::cout << "A()" << std::endl;
        //throw 10;
    }
    ~A() noexcept(false)
    {
        std::cout << "~A()" << std::endl;
        throw 10;
        delete[] data_;
    }
private:
    int* data_{nullptr};
};

int main()
{
    try
    {
        A a;
    }
    catch(...)
    {
        std::cout << "catched" << std::endl;
    }
}
