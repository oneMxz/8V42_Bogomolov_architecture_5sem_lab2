cmake_minimum_required(VERSION 3.10.0)
project(lab2_archi VERSION 0.1.0 LANGUAGES CXX)

add_executable(lab2_archi main.cpp tasks.cpp)

target_compile_options(lab2_archi PRIVATE -O2)

message(STATUS "Optimization flags: -O2")