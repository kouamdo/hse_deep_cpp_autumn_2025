#include <iostream>
#include <thread>
#include <chrono>
#include <source_location>

struct Profiler
{
    Profiler(const std::source_location& location = std::source_location::current()) {
        location_ = location;
        start_ts_ = std::chrono::system_clock::now();
    }
    ~Profiler() {
        auto end_ts_ = std::chrono::system_clock::now();
        uint64_t delta =  std::chrono::duration_cast<std::chrono::milliseconds>(end_ts_ - start_ts_).count();
        std::cout << "Time of execution of [" << location_.function_name() << " | " << location_.file_name() <<  "] is " << delta << " milliseconds" << std::endl;
    }
private:
    std::chrono::time_point<std::chrono::system_clock> start_ts_;
    std::source_location location_;
};

void foo()
{
    Profiler prof;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    for(size_t i = 0; i < 100000000; ++i);
}

void boo()
{
    Profiler prof;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for(size_t i = 0; i < 200000000; ++i);
}

int main()
{
    foo();
    boo();
}
