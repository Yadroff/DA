#ifndef KP_DEFINITIONS_H
#define KP_DEFINITIONS_H

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <complex>
#include <cstring>
#include <mpg123.h>

#define all(v) v.begin(), v.end()

typedef uint64_t Size;
typedef std::complex<double> Complex;

const Size BLOCK_SIZE = 4096;
const Size RANGE_NUM = 5;
const Size RANGES[RANGE_NUM] = {40, 80, 120, 180, 300};
const Size RANGE_MIN = 40;
const Size RANGE_MAX = 300;
const Size HASH_CONST = 2;
const std::string LIBRARY_PATH = std::string("./LIBRARY/");
const std::string LIB_FILE = std::string("./LIBRARY/LIB_FILE.txt");
const long RATE = 44100;
#endif //KP_DEFINITIONS_H
