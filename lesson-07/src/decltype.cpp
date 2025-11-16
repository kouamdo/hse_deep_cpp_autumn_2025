#include <cstdint>
#include <vector>
#include <map>
#include <iostream>

template<class Container, class Index>
auto authAndAccess(const Container& c, Index i) -> decltype(c.at(i))
{
    // auth
    return c.at(i);
}

int main()
{
    using vec_t = std::vector<int32_t>;
    vec_t arr(100, -1);
    std::cout << authAndAccess<vec_t, std::size_t>(arr, 10) << std::endl;

    std::map<std::string, std::vector<double>> m;
    m["100"] = {1.0, 5.0, 10.5};
    m["cat"] = {1.0, 5.0, 10.5};
    std::cout << authAndAccess(m, "100").back() << std::endl;
    //std::map<std::string, std::vector<double>>::iterator it = m.begin();
    auto it = m.begin();
    for (; it != m.end(); ++it)
    {
        std::cout << it->first << std::endl;
    }
}
