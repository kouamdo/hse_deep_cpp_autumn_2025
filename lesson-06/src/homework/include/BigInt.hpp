#ifndef BIGINT
#define BIGINT

#include <cstdint>
#include <stdexcept>
#include <iostream>

class BigInt{
    private:
        char* number;
        size_t number_length ;
        bool pos ;

    public:
        BigInt(const char* number);
        BigInt() ;
        BigInt(const BigInt& other);
        BigInt(BigInt& other);
        ~BigInt();
        bool operator==( BigInt& other) const;
        bool operator!=( BigInt& other) const;
        bool operator<(const BigInt& other) const ;
        bool operator>( BigInt& other) const;
        bool operator<=( BigInt& other) const;
        bool operator>=( BigInt& other) const;
        friend std::ostream& operator<<(std::ostream& os, const BigInt& bi);
        BigInt& operator+(const BigInt& other) const;
        BigInt& operator-(const BigInt& other) const;
        BigInt& operator*(int32_t rhs) const;
        BigInt& operator-(int32_t rhs) const;
        BigInt& operator+(int32_t rhs) const;
    };

#endif