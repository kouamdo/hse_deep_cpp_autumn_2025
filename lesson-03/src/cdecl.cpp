void foo1(int a, int b, int c, int d, int e, int f, int g, double h)
{
}

void foo2(int a, int b, int c, int d)
{
}

void foo3(long long a)
{
}

void boo1()
{
    foo1(1, 2, 3, 4, 5, 6, 7, 1.2);
}

void boo2()
{
    foo2(1, 2, 3, 4);
}

void boo3()
{
    foo3(100ll);
}
