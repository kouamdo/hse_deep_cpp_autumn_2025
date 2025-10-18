module;

#include <iostream>

export module mexample;

export int square(int value) { return value * value; }

export void foo() { }

export namespace search
{
    void boo() {}
    void foo() {}
}

export
{
    void foo1() {}
    void foo2() {}
};
