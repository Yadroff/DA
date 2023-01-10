cmake_minimum_required(VERSION 3.24)
project(KP)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -lmpg123)
add_executable(KP main.cpp Definitions.h Shazam.cpp Shazam.h)
