cmake_minimum_required(VERSION 3.23)
project(SUFF_TREE)

set(CMAKE_CXX_STANDARD 20)

add_executable(solution main.cpp SuffTree.cpp SuffTree.h)
add_executable(naieve naieve.cpp)
