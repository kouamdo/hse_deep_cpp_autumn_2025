#include "../include/BigInt.hpp"
#include <cstring>
#include <cstdlib>

// Helper: remove leading zeros in magnitude representation
void BigInt::trim() {
    while (size_ > 1 && digits_[size_ - 1] == 0) {
        --size_;
    }
    if (size_ == 1 && digits_[0] == 0) positive_ = true; // zero is positive
}

int BigInt::absCompare(const BigInt& a, const BigInt& b) {
    if (a.size_ != b.size_) return a.size_ > b.size_ ? 1 : -1;
    for (size_t i = a.size_; i-- > 0;) {
        if (a.digits_[i] != b.digits_[i]) return a.digits_[i] > b.digits_[i] ? 1 : -1;
    }
    return 0;
}

BigInt BigInt::addMag(const BigInt& a, const BigInt& b) {
    size_t n = std::max(a.size_, b.size_);
    BigInt res;
    delete[] res.digits_;
    res.digits_ = new char[n + 1];
    res.size_ = n + 1;
    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        int da = i < a.size_ ? a.digits_[i] : 0;
        int db = i < b.size_ ? b.digits_[i] : 0;
        int sum = da + db + carry;
        res.digits_[i] = sum % 10;
        carry = sum / 10;
    }
    res.digits_[n] = carry;
    res.trim();
    return res;
}

BigInt BigInt::subMag(const BigInt& a, const BigInt& b) {
    // assumes |a| >= |b|
    BigInt res;
    delete[] res.digits_;
    res.digits_ = new char[a.size_];
    res.size_ = a.size_;
    int borrow = 0;
    for (size_t i = 0; i < a.size_; ++i) {
        int da = a.digits_[i];
        int db = i < b.size_ ? b.digits_[i] : 0;
        int diff = da - db - borrow;
        if (diff < 0) { diff += 10; borrow = 1; }
        else borrow = 0;
        res.digits_[i] = diff;
    }
    res.trim();
    return res;
}

// Constructors / dtor / assign
BigInt::BigInt() {
    size_ = 1;
    digits_ = new char[1];
    digits_[0] = 0;
    positive_ = true;
}

BigInt::BigInt(const char* s) {
    if (!s) throw std::invalid_argument("null string");
    std::string str(s);
    // remove leading/trailing spaces
    size_t pos = 0;
    while (pos < str.size() && isspace(static_cast<unsigned char>(str[pos]))) ++pos;
    size_t end = str.size();
    while (end > pos && isspace(static_cast<unsigned char>(str[end - 1]))) --end;
    if (pos >= end) throw std::invalid_argument("empty string");
    bool sign = true;
    if (str[pos] == '+') { sign = true; ++pos; }
    else if (str[pos] == '-') { sign = false; ++pos; }
    if (pos >= end) throw std::invalid_argument("no digits");
    // skip leading zeros
    while (pos < end && str[pos] == '0') ++pos;
    if (pos == end) {
        // zero
        size_ = 1;
        digits_ = new char[1]; digits_[0] = 0; positive_ = true; return;
    }
    size_ = end - pos;
    digits_ = new char[size_];
    for (size_t i = 0; i < size_; ++i) {
        char c = str[end - 1 - i]; // least significant first
        if (c < '0' || c > '9') { delete[] digits_; digits_ = nullptr; throw std::invalid_argument("bad digit"); }
        digits_[i] = c - '0';
    }
    positive_ = sign;
    trim();
}

BigInt::BigInt(const std::string& s) : BigInt(s.c_str()) {}

BigInt::BigInt(const BigInt& other) {
    size_ = other.size_;
    positive_ = other.positive_;
    digits_ = new char[size_];
    for (size_t i = 0; i < size_; ++i) digits_[i] = other.digits_[i];
}

BigInt::BigInt(BigInt&& other) noexcept {
    digits_ = other.digits_;
    size_ = other.size_;
    positive_ = other.positive_;
    other.digits_ = nullptr;
    other.size_ = 0;
    other.positive_ = true;
}

BigInt& BigInt::operator=(const BigInt& other) {
    if (this == &other) return *this;
    delete[] digits_;
    size_ = other.size_;
    positive_ = other.positive_;
    digits_ = new char[size_];
    for (size_t i = 0; i < size_; ++i) digits_[i] = other.digits_[i];
    return *this;
}

BigInt& BigInt::operator=(BigInt&& other) noexcept {
    if (this == &other) return *this;
    delete[] digits_;
    digits_ = other.digits_;
    size_ = other.size_;
    positive_ = other.positive_;
    other.digits_ = nullptr;
    other.size_ = 0;
    other.positive_ = true;
    return *this;
}

BigInt::~BigInt() {
    delete[] digits_;
}

std::string BigInt::toString() const {
    std::string s;
    if (!positive_) s.push_back('-');
    for (size_t i = 0; i < size_; ++i) s.push_back(char('0' + digits_[size_ - 1 - i]));
    return s;
}

// comparisons
bool BigInt::operator==(const BigInt& other) const {
    if (positive_ != other.positive_) return false;
    if (size_ != other.size_) return false;
    for (size_t i = 0; i < size_; ++i) if (digits_[i] != other.digits_[i]) return false;
    return true;
}

bool BigInt::operator!=(const BigInt& other) const { return !(*this == other); }

bool BigInt::operator<(const BigInt& other) const {
    if (positive_ != other.positive_) return !positive_;
    int cmp = absCompare(*this, other);
    if (positive_) return cmp < 0;
    else return cmp > 0;
}

bool BigInt::operator>(const BigInt& other) const { return other < *this; }
bool BigInt::operator<=(const BigInt& other) const { return !(*this > other); }
bool BigInt::operator>=(const BigInt& other) const { return !(*this < other); }

// arithmetic
BigInt BigInt::operator+(const BigInt& other) const {
    if (positive_ == other.positive_) {
        BigInt res = addMag(*this, other);
        res.positive_ = positive_;
        return res;
    } else {
        int cmp = absCompare(*this, other);
        if (cmp == 0) return BigInt();
        if (cmp > 0) { // |this| > |other|
            BigInt res = subMag(*this, other);
            res.positive_ = positive_;
            return res;
        } else {
            BigInt res = subMag(other, *this);
            res.positive_ = other.positive_;
            return res;
        }
    }
}

BigInt BigInt::operator-(const BigInt& other) const {
    if (positive_ != other.positive_) {
        BigInt res = addMag(*this, other);
        res.positive_ = positive_;
        return res;
    } else {
        int cmp = absCompare(*this, other);
        if (cmp == 0) return BigInt();
        if (cmp > 0) {
            BigInt res = subMag(*this, other);
            res.positive_ = positive_;
            return res;
        } else {
            BigInt res = subMag(other, *this);
            res.positive_ = !other.positive_;
            return res;
        }
    }
}

BigInt BigInt::operator*(const BigInt& other) const {
    BigInt res;
    delete[] res.digits_;
    res.size_ = size_ + other.size_;
    res.digits_ = new char[res.size_];
    for (size_t i = 0; i < res.size_; ++i) res.digits_[i] = 0;
    for (size_t i = 0; i < size_; ++i) {
        int carry = 0;
        for (size_t j = 0; j < other.size_; ++j) {
            int cur = res.digits_[i + j] + digits_[i] * other.digits_[j] + carry;
            res.digits_[i + j] = cur % 10;
            carry = cur / 10;
        }
        res.digits_[i + other.size_] += carry;
    }
    res.positive_ = (positive_ == other.positive_);
    res.trim();
    return res;
}

BigInt BigInt::operator+(int32_t rhs) const { return *this + BigInt(std::to_string(rhs)); }
BigInt BigInt::operator-(int32_t rhs) const { return *this - BigInt(std::to_string(rhs)); }
BigInt BigInt::operator*(int32_t rhs) const { return *this * BigInt(std::to_string(rhs)); }

BigInt BigInt::operator-() const { BigInt r(*this); r.positive_ = !r.positive_; return r; }
