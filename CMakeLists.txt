cmake_minimum_required(VERSION 3.6)
project(ditwo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        Src/Structures/Vector.cpp
        Src/Structures/Vector.h
        Src/Allocators/Allocator.cpp
        Src/Allocators/Allocator.h)
ADD_LIBRARY(ditwo STATIC ${SOURCE_FILES})