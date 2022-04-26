cmake_minimum_required(VERSION 3.21)
project(2lab)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
add_executable(2lab main.cpp)
