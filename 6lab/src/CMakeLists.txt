cmake_minimum_required(VERSION 3.24)
project(6lab)

set(CMAKE_CXX_STANDARD 20)

add_executable(6lab main.cpp
        BigInt.cpp BigInt.h
        Fourier.cpp Fourier.h
        Constructors.cpp Predicates.cpp ArithmeticOperations.cpp)
