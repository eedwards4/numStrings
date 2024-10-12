cmake_minimum_required(VERSION 3.29)
project(numStrings)

set(CMAKE_CXX_STANDARD 20)

add_executable(numStrings numStrings.cpp
        mini-gmp/mini-gmp.c mini-gmp/mini-gmp.h
        mini-gmp/mini-mpq.c mini-gmp/mini-mpq.h
)
