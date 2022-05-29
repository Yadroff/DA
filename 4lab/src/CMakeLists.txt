cmake_minimum_required(VERSION 3.20)
project(4lab/src)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -pg -fsanitize=address")
add_executable(main main.cpp TWord.cpp)