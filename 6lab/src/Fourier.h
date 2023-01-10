#ifndef INC_6LAB_FOURIER_H
#define INC_6LAB_FOURIER_H

#include <vector>
#include <complex>

#define all(v) v.begin(), v.end()

typedef std::complex<double> complex;

class Fourier {
public:
    static void fft(std::vector<complex> &, bool invert);

    static void multiply(const std::vector<int> &a, const std::vector<int> &b,
                         std::vector<unsigned long long> &res);
};


#endif //INC_6LAB_FOURIER_H
