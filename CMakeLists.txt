cmake_minimum_required(VERSION 3.9)
project(comp_prog)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(comp_prog tasks/scheduling/main.cpp)