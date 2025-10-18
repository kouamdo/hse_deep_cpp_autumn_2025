#include <iostream>

class Logger
{
public:
    void print(const std::string& message)
    {
        std::cout << "[INFO] " << message << std::endl;
        bytes_cnt_ += message.size();
    }
private:
    size_t bytes_cnt_;
};

class Dachshund
{
//private:
    Dachshund(const Dachshund& rhs) = delete;

public:
    // Конструктор по-умолчанию.
    /*Dachshund()
    {
        std::cout << "default ctr" << std::endl;
    }*/

    // Пользовательский конструктор
    Dachshund(const std::string& name) : age_(19), name_(name)
    {
        std::cout << "user ctr" << std::endl;
    }

    // Пользовательский конструктор (ещё один)
    /*Dachshund(uint8_t age)
    {
        age_ = age;
        std::cout << "ctr" << std::endl;
    }*/

    void feed() const
    {
        logger_.print("It's feed time!");
        std::cout << "feed" << std::endl;
    }

    // Деструктор
    ~Dachshund()
    {
        std::cout << "dctr" << std::endl;
    }
private:
    uint8_t age_{0}; // закрытый член класса
    const std::string& name_;
    mutable Logger logger_;
};

void foo(const Dachshund& dachshund)
{
    dachshund.feed();
}

int main()
{
    std::cout << "start" << std::endl;
    {
        std::string name = "Roksana";
        Dachshund roksy(name);
        roksy.feed();
        foo(roksy);
        //Dachshund shokolad = roksy; // копирующий конструктор
    }
    std::cout << "end" << std::endl;
}
