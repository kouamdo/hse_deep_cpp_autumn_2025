#include <stdlib.h>

int fibonacci(int n)
{
    if (n < 2)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int sum(int* arr, unsigned int len)
{
    int res = 0;
    for (unsigned int i = 0; i < len; ++i)
    {
        res += arr[i];
    }
    return res;
}
