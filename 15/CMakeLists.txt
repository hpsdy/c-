# cmake_minimum_required(VERSION <specify CMake version here>)
project(15)

set(CMAKE_CXX_STANDARD 11)

add_executable(15 main.cpp text/include/query_base.h text/include/WordQuery.h text/include/NotQuery.h text/include/BinaryQuery.h text/include/AndQuery.h text/include/OrQuery.h)