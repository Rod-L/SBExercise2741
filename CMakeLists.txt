cmake_minimum_required(VERSION 3.22)
project(SBExercise2741)

set(CMAKE_CXX_STANDARD 14)

add_executable(SBExercise2741
        src/Branch.cpp
        include/Branch.h
        src/main.cpp)

target_include_directories(SBExercise2741 PUBLIC include)
