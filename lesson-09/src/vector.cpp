#include <iostream>

template<class T>
class vector
{
public:
    vector() = default;
    ~vector()
    {
        delete[] data_;
    }

    void push_back(const T& obj)
    {
        if (size_ == capacity_)
        {
            capacity_ = capacity_ ? capacity_ * 2 : 1;
            T* tmp = new T[capacity_];
            if (data_)
            {
                for (size_t i = 0; i < size_; ++i)
                    tmp[i] = std::move(data_[i]);
            }
            delete[] data_;
            data_ = tmp;
        }
        data_[size_++] = obj;
    }
private:
    T* data_{nullptr};
    size_t size_{0};
    size_t capacity_{0};
};

int main()
{
    {
        // O(n * n)
        // 1 + 2 + 4 + 8 + ... + n/2 + n = n(1+ 1/2 + 1/4 + 1/8 + ...) = O(2n) = O(n)
        vector<char> v;
        v.push_back('a');
        v.push_back('b');
        v.push_back('c');
    }

    {
        std::vector<char> v = {'a', 'b', 'c'};
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        auto it = std::begin(v);
        // [a][b][c]
        //  |
        //  it
        v.push_back('d');
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        // [a][b][c][d]
        // [x][x][x]
        //  |
        //  it
        std::cout << "iterator value = " << *it << std::endl;
        v.push_back('e');
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        v.push_back('f');
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        v.push_back('g');
        std::cout << v.size() << ":" << v.capacity() << std::endl;

    }
    {
        std::vector<char> v(100, '0');
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        v.resize(15);
        v.shrink_to_fit();
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        v.clear();
        std::cout << v.size() << ":" << v.capacity() << std::endl;
        std::vector<char>().swap(v);
        std::cout << v.size() << ":" << v.capacity() << std::endl;
    }

}
