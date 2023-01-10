#ifndef INC_6LAB_BIGINT_H
#define INC_6LAB_BIGINT_H

#include <iostream>
#include <vector>
#include <exception>

#include "Fourier.h"

class BigInt {
public:
    BigInt();

    BigInt(const std::string &str);

    BigInt(signed char);

    BigInt(unsigned char);

    BigInt(signed short);

    BigInt(unsigned short);

    BigInt(signed int);

    BigInt(unsigned int);

    BigInt(signed long);

    BigInt(unsigned long);

    BigInt(signed long long);

    BigInt(unsigned long long);

    friend std::ostream &operator<<(std::ostream &os, const BigInt &anInt);

    explicit operator std::string() const;

    friend bool operator==(const BigInt &left, const BigInt &right);

    friend bool operator<(const BigInt &left, const BigInt &right);

    friend bool operator!=(const BigInt &left, const BigInt &right);

    friend bool operator>(const BigInt &left, const BigInt &right);

    friend bool operator>=(const BigInt &left, const BigInt &right);

    friend bool operator<=(const BigInt &left, const BigInt &right);

    BigInt operator+() const;

    BigInt operator-() const;

    friend BigInt operator+(const BigInt &left, const BigInt &right);

    friend BigInt operator-(const BigInt &left, const BigInt &right);

    BigInt &operator+=(const BigInt &val);

    BigInt &operator-=(const BigInt &val);

    BigInt &operator++();

    BigInt operator++(int);

    BigInt &operator--();

    BigInt operator--(int);

    BigInt &operator*=(const BigInt &val);

    friend BigInt operator*(const BigInt &left, const BigInt &right);

    friend BigInt operator/(const BigInt &left, const BigInt &right);

    friend BigInt operator/(const BigInt &left, long long right);

    [[nodiscard]] long long toLL() const;

    [[nodiscard]] long double toDouble() const;

    BigInt &operator/=(const BigInt &val);

    friend BigInt operator^(BigInt a, BigInt n);

    friend BigInt operator^(BigInt a, unsigned long long n);

    int operator[](size_t index) const;

    bool odd(); // нечетное число

    bool even(); // четное число

    void shiftRight(); // смещение вправо на один разряд

private:
    void deleteLeadingZeroes();

    bool negative_;
    std::vector<int> digits_;
    static const int BASE = 10000;
    static const int LENGTH = 4;
};


#endif //INC_6LAB_BIGINT_H
