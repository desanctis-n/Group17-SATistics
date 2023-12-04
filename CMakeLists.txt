cmake_minimum_required(VERSION 3.26)
project(Group17_SATistics)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Group17_SATistics
        Heap.cpp
        main.cpp
        quickSort.h
        Scores.cpp
        Scores.h
        statics.cpp)
