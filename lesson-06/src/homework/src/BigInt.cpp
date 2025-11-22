#include "../include/BigInt.hpp"
#include <string.h>

BigInt::BigInt() 
{
        number_length = 1;
        number = new char[1]{0};
        pos = true;
}

BigInt::BigInt(const BigInt& other)
{
    pos = other.pos ;
    number_length = other.number_length ;
    number = new char[number_length];
    for (size_t i = 0; i < number_length; i++)
        number[i] = other.number[i];
}

BigInt::BigInt(BigInt& other) noexcept
{
    pos = other.pos ;
    number_length = other.number_length ;
    number = new char[number_length];
    for (size_t i = 0; i < number_length; i++)
        number[i] = other.number[i];
}

BigInt::~BigInt() {
    delete[] number;
}

BigInt::BigInt(const char* numberchar)  {

    number_length = strlen(numberchar) ;

    size_t i = 0 ; pos = true;

    if (numberchar[i] == '-') {
        pos = false ; i = 1 ; number_length -- ;
    } 

    number = new char[number_length] ;

    while (i < number_length && (numberchar[i] > '0' ||  numberchar[i] < '9') )
    {
        number[i] = numberchar[i] - '0';

        i++;
    }

    if (i < number_length ) 
    {
        throw std::invalid_argument("bad and signed content") ;
        delete[] number ;
        pos = false ;
    }
}

bool BigInt::operator==(BigInt& other) const {
    if (pos != other.pos) return false;
    if (number_length != other.number_length) return false;
    for (size_t i = 0; i < number_length; i++) {
        if (number[i] != other.number[i]) return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bi) {
    if (!bi.pos) os << '-';
    for (size_t i = 0; i < bi.number_length; i++) {
        os << static_cast<int>(bi.number[i]);
    }
    return os;
}


bool BigInt::operator!=(BigInt& other) const {
    return !(*this == other);
}

bool BigInt::operator<(const BigInt& other) const {
    if (pos != other.pos) return !pos; // négatif < positif
    if (pos) { // deux positifs
        if (number_length != other.number_length)
            return number_length < other.number_length;
        for (size_t i = 0; i < number_length; i++) {
            if (number[i] != other.number[i])
                return number[i] < other.number[i];
        }
        return false; // égaux
    } else { // deux négatifs (inverser la logique)
        if (number_length != other.number_length)
            return number_length > other.number_length;
        for (size_t i = 0; i < number_length; i++) {
            if (number[i] != other.number[i])
                return number[i] > other.number[i];
        }
        return false;
    }
}

bool BigInt::operator>(BigInt& other) const {
    return other < *this;
}

// Plus petit ou égal
bool BigInt::operator<=( BigInt& other) const {
    return !(*this > other);
}

// Plus grand ou égal
bool BigInt::operator>=( BigInt& other) const {
    return !(*this < other);
}

BigInt& BigInt::operator+(const BigInt& other) const {
        size_t max_len = std::max(number_length, other.number_length);
        BigInt result;
        result.pos = true;
        delete[] result.number;
        result.number = new char[max_len + 1]; // +1 pour la retenue possible
        result.number_length = max_len;

        int carry = 0;
        size_t i = 0;
        for (; i < max_len; i++) {
            int a_digit = i < number_length ? number[number_length - 1 - i] : 0;  // chiffres de droite à gauche
            int b_digit = i < other.number_length ? other.number[other.number_length - 1 - i] : 0;
            int sum = a_digit + b_digit + carry;
            result.number[max_len - i] = sum % 10; // stocker chiffre
            carry = sum / 10;
        }
        if (carry > 0) {
            // on décale le tableau pour ajouter la retenue en tête
            char* temp = new char[max_len + 2];
            temp[0] = carry;
            for (i = 0; i <= max_len; i++)
                temp[i + 1] = result.number[i];
            delete[] result.number;
            result.number = temp;
            result.number_length = max_len + 1;
        }
        return result;
    }

BigInt& BigInt::operator-(const BigInt& other) const {
    if (*this < other) {
        throw std::invalid_argument("Soustraction non supportée pour this < other dans cette version simple");
    }

    BigInt result;
    result.pos = true;
    delete[] result.number;
    result.number = new char[number_length];
    result.number_length = number_length;

    int borrow = 0;
    for (size_t i = 0; i < number_length; i++) {
        int a_digit = number[number_length - 1 - i];
        int b_digit = i < other.number_length ? other.number[other.number_length - 1 - i] : 0;

        int diff = a_digit - b_digit - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.number[result.number_length - 1 - i] = diff;
    }

    // Supprimer les zéros non significatifs en tête
    size_t new_len = result.number_length;
    while (new_len > 1 && result.number[result.number_length - new_len] == 0) {
        --new_len;
    }

    if (new_len != result.number_length) {
        char* trimmed = new char[new_len];
        for (size_t i = 0; i < new_len; i++) {
            trimmed[i] = result.number[result.number_length - new_len + i];
        }
        delete[] result.number;
        result.number = trimmed;
        result.number_length = new_len;
    }

    return result;
}

BigInt& BigInt::operator+(int32_t rhs) const {
    BigInt rhsBigInt(std::to_string(rhs).c_str());
    return *this + rhsBigInt;  // utilise l'opérateur BigInt + BigInt
}

// Soustraction BigInt - int32_t
BigInt& BigInt::operator-(int32_t rhs) const {
    BigInt rhsBigInt(std::to_string(rhs).c_str());
    return *this - rhsBigInt;  // utilise l'opérateur BigInt - BigInt
}

// Multiplication BigInt * int32_t
BigInt& BigInt::operator*(int32_t rhs) const {
    BigInt rhsBigInt(std::to_string(rhs).c_str());
    return *this * rhsBigInt;  // utilise l'opérateur BigInt * BigInt
}