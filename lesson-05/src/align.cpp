#include <iostream>

struct S
{
    double m2;
    char m1;
};

struct S1
{
    char m3;
    char m4;
    int32_t m1;
    double m2;
};

class NonPOD
{
    NonPOD()
    {
        m1 = 100;
    }
    int m1;
};

int main()
{
    std::cout << sizeof(char) << std::endl;
    std::cout << sizeof(double) << std::endl;
    std::cout << sizeof(S) << std::endl;
    std::cout << alignof(char) << std::endl;
    std::cout << alignof(double) << std::endl;
    std::cout << "============= S1 =============" << std::endl;
    std::cout << sizeof(char) << std::endl;
    std::cout << sizeof(double) << std::endl;
    std::cout << sizeof(int32_t) << std::endl;
    std::cout << sizeof(S1) << std::endl;

    std::cout << std::boolalpha << std::is_pod<S1>::value << std::endl;
    std::cout << std::boolalpha << std::is_trivial<S1>::value << std::endl;
    std::cout << std::boolalpha << std::is_standard_layout<S1>::value << std::endl;
    std::cout << std::boolalpha << std::is_pod<NonPOD>::value << std::endl;
    std::cout << std::boolalpha << std::is_trivial<NonPOD>::value << std::endl;
    std::cout << std::boolalpha << std::is_standard_layout<NonPOD>::value << std::endl;
    return 0;
}
