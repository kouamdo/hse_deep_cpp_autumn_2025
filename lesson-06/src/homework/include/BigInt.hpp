#ifndef BIGINT
#define BIGINT

#include <cstdint>
#include <stdexcept>
#include <iostream>

class BigInt{
    private:
        char* number;
        size_t number_length ;
        bool pos = true ;
        int64_t bigNumber;

    public:
        BigInt(const char* number);

}

#endif