#ifndef BIGINT
#define BIGINT

#include <cstdint>
#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>

class BigInt {
private:
    // digits in little-endian order: digits_[0] is least significant digit (0-9)
    char* digits_ = nullptr;
    size_t size_ = 0;
    bool positive_ = true; // true => non-negative

    void trim();
    static int absCompare(const BigInt& a, const BigInt& b); // 1 if |a|>|b|, 0 if equal, -1 if |a|<|b|
    static BigInt addMag(const BigInt& a, const BigInt& b);
    static BigInt subMag(const BigInt& a, const BigInt& b); // assumes |a|>=|b|

public:
    BigInt();
    explicit BigInt(const char* s);
    explicit BigInt(const std::string& s);

    // copy/move
    BigInt(const BigInt& other);
    BigInt(BigInt&& other) noexcept;
    BigInt& operator=(const BigInt& other);
    BigInt& operator=(BigInt&& other) noexcept;
    ~BigInt();

    // conversions
    std::string toString() const;

    // arithmetic
    BigInt operator+(const BigInt& other) const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;

    // int32_t overloads
    BigInt operator+(int32_t rhs) const;
    BigInt operator-(int32_t rhs) const;
    BigInt operator*(int32_t rhs) const;

    BigInt operator-() const; // unary minus

    // comparisons
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;

    friend std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
        os << bi.toString();
        return os;
    }
};

#endif