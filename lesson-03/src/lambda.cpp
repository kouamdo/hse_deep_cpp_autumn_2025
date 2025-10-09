#include <vector>
#include <iostream>
#include <unordered_map>

int main()
{
    std::vector<int> arr = {2, 1, 4, 2, 1, 6};
    std::unordered_map<int, bool> cache;
    auto pred = [&cache](int num) {
        if (auto it = cache.find(num); it != cache.end())
        {
            std::cout << "Found in cache " << num << " = " << it->second << "\n";
            return it->second;
        }

        bool res = num % 2 == 0;
        cache[num] = res;
        return res;
    };
    std::for_each(std::begin(arr), std::end(arr), pred);
    return 0;
}
