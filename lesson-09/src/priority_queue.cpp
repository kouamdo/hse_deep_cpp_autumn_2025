#include <iostream>
#include <vector>
#include <queue>

int main()
{
    const size_t k = 3;
    {
        std::vector<int32_t> v = {10, 2, 1, 8, 9, 1, 4, 3, 6};
        // O(n log n)
        std::sort(std::begin(v), std::end(v), std::greater<int32_t>());
        for(size_t i = 0; i < k; ++i)
        {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    }
    {
        // O(n log k)
        //std::priority_queue<int32_t> pq;
    }
}
