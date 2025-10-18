#include <iostream>

class Integer
{
public:
    Integer() = default;
    Integer(int64_t num) : num_(num) {}

    Integer operator+(const Integer& rhs) const
    {
        Integer tmp;
        tmp.num_ = num_ + rhs.num_;
        return tmp;
    }

    // ++i
    Integer& operator++()
    {
        num_ += 1;
        return *this;
    }

    // i++
    Integer operator++(int)
    {
        Integer tmp{num_};
        num_ += 1;
        return tmp;
    }

    friend std::ostream& operator<<(std::ostream& out, const Integer& rhs);
private:
    int64_t num_{0};
};

std::ostream& operator<<(std::ostream& out, const Integer& rhs)
{
    out << rhs.num_;
    return out;
}


int main()
{
    Integer i1{43};
    Integer i2{10};
    ++i1;
    i1++;
    std::cout << i1+i2 << std::endl;
    //(i1+i2) << std::cout << std::endl;
}
