#include <iostream>

struct A
{
    virtual void common()
    {
        std::cout << "A::common" << std::endl;
    }
};

struct B : public A
{
    void common() override
    {
        std::cout << "B::common" << std::endl;
    }

    void magicB()
    {
        std::cout << "B::magicB" << std::endl;
    }

};

struct C : public A
{
    void common() override
    {
        std::cout << "C::common" << std::endl;
    }

    void magicB()
    {
        std::cout << "C::magicB" << std::endl;
    }

};

void foo(A* a)
{
    a->common();
    B* b = dynamic_cast<B*>(a);
    if (b != nullptr)
    {
        b->magicB();
    }
    else
    {
        std::cerr << "Failed to cast to B" << std::endl;
    }
}

void boo(A& a)
{
    a.common();
    B& b = dynamic_cast<B&>(a);
    b.magicB();
}

int main()
{
    {
        A* a = new C;
        foo(a);
    }
    {
        B c;
        A& a = c;
        boo(a);
    }
    return 0;
}

