cmake_minimum_required(VERSION 3.28)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled source/maze.c
        source/pos.c
        header/pos.h
        header/stack.h
)
