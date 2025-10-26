#include <iostream>
#include <cstring>

namespace my
{

class string
{
public:
    string(const char* str) : size_(strlen(str)), capacity_(size_)
    {
        data_ = new char[size_];
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = str[i];
        }
    }

    string(const string& str) : size_(str.size_), capacity_(str.capacity_), data_(new char[str.capacity_])
    {
        for (size_t i = 0; i < size_; ++i)
        {
            data_[i] = str.data_[i];
        }
    }

    /*
    string& operator=(const string& rhs) = default;
    {
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        data_ = rhs.data_;
    }
    */

    ~string()
    {
        delete[] data_;
    }
private:
    size_t size_{0};
    size_t capacity_{0};
    char* data_{nullptr};
};

} // namespace my

int main()
{
    my::string str1{"Hello"};
    my::string str2 = str1;
    str2 = str1;
}
