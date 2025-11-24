#include <iostream>
#include <tuple>
#include <format>

int main()
{
    std::cout << std::format("{} === {}", "Hello", 2) << std::endl;
    {
        auto t = std::make_tuple(1, 2.0, "abc");
        int a = std::get<0>(t);
        double b = std::get<1>(t);
        std::string c = std::get<2>(t);
    }
    {
        auto t = std::tuple<int32_t, double, std::string>{1, 2.0, "abc"};
        auto [a, b, c] = t;
    }
}
