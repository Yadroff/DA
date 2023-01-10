#include "BigInt.h"
#include <iomanip>

BigInt::BigInt() : negative_(false), digits_(1, 0) {}

BigInt::BigInt(signed char c) {
    negative_ = (c < 0);
    digits_.emplace_back(std::abs(c));
}

BigInt::BigInt(unsigned char c) {
    negative_ = false;
    digits_.emplace_back(c);
}

BigInt::BigInt(short sh) {
    negative_ = (sh < 0);
    digits_.emplace_back(std::abs(sh));
}

BigInt::BigInt(unsigned short c) {
    negative_ = false;
    digits_.emplace_back(c);
}

BigInt::BigInt(int l) {
    negative_ = (l < 0);
    l = std::abs(l);
    do {
        this->digits_.emplace_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

BigInt::BigInt(unsigned int l) {
    negative_ = false;
    do {
        this->digits_.emplace_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

BigInt::BigInt(long l) {
    negative_ = (l < 0);
    l = std::abs(l);
    do {
        this->digits_.emplace_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

BigInt::BigInt(unsigned long l) {
    negative_ = false;
    do {
        this->digits_.emplace_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

BigInt::BigInt(long long int l) {
    negative_ = (l < 0);
    l = std::abs(l);
    do {
        this->digits_.emplace_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

BigInt::BigInt(unsigned long long int l) {
    negative_ = false;
    do {
        this->digits_.emplace_back(l % BigInt::BASE);
        l /= BigInt::BASE;
    } while (l != 0);
}

BigInt::BigInt(const std::string &str) {
    negative_ = false;
    if (str.empty()) {
        digits_.resize(1, 0); // для однозначного представления нуля
    } else {
        std::string digits = str;
        if (str[0] == '-' or str[0] == '+') {
            digits = str.substr(1);
            negative_ = (str[0] == '-');
        }
        for (long long i = digits.size(); i > 0; i -= LENGTH) {
            if (i < LENGTH) {
                digits_.emplace_back(std::atoi(digits.substr(0, i).c_str()));
            } else {
                digits_.emplace_back(std::atoi(digits.substr(i - BigInt::LENGTH, BigInt::LENGTH).c_str()));
            }
        }
        deleteLeadingZeroes();
    }
}

std::ostream &operator<<(std::ostream &os, const BigInt &anInt) {
    if (anInt.digits_.empty()) {
        os << 0;
        return os;
    }
    if (anInt.negative_) {
        os << '-';
    }
    os << anInt.digits_.back();
    /*if (anInt.digits_.size() > 1) {
        os << "\'";
    }*/
    for (long long i = anInt.digits_.size() - 2; i >= 0; --i) {
        os << std::setw(BigInt::LENGTH) << std::setfill('0') << anInt.digits_[i];
/*        if (i != 0) {
            os << "\'";
        }*/
    }
    return os;
}

BigInt::operator std::string() const {
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

void BigInt::deleteLeadingZeroes() {
    while (digits_.size() > 1 and digits_.back() == 0) {
        digits_.pop_back();
    }
    if (digits_.size() == 1 and digits_.back() == 0) {
        negative_ = false;
    }
}