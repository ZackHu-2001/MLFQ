cmake_minimum_required(VERSION 3.26)
project(MLFQ)

set(CMAKE_CXX_STANDARD 17)

add_executable(MLFQ main.cpp
        src/MLFQ.cpp
        src/MLFQ.h
        src/Queue.cpp
        src/Queue.h
        src/Process.cpp
        src/Process.h)
