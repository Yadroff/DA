cmake_minimum_required(VERSION 3.23)
project(src)

set(CMAKE_CXX_STANDARD 14)

set(HEADERS
        Equation.h
        SystemOfEquations.h)
set(SOURCES
        Equation.cpp
        SystemOfEquations.cpp)
add_executable(solution ${HEADERS} ${SOURCES} main.cpp)
add_executable(native native_2.cpp)
