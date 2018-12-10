cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(xgrep)

add_executable(${PROJECT_NAME}
    src/args.h
    src/args.c
    src/main.c
    src/result.h
    src/result.c
    src/util.h
    src/vector.h
)
