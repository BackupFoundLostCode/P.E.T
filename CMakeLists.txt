cmake_minimum_required(VERSION 4.2)
project(P_E_T)

set(CMAKE_CXX_STANDARD 26)

include_directories(.)

add_executable(P_E_T
        FileStealer.cpp
        functions.hpp)
