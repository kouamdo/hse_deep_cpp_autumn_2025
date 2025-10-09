#include <memory>

[[deprecated]]
int square(int num)
{
    return num * num;
}

[[nodiscard("You must use returned value")]]
uint32_t get_status()
{
    return 404;
}

void foo([[maybe_unused]] int num)
{
}

int main()
{
    std::auto_ptr<int> aptr;
    [[maybe_unused]] auto status = get_status();
    if (status == 200) [[unlikely]]
    {
    }
    else [[likely]] {
    }
    foo(10);
    
    return square(4);
}
