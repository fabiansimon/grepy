cmake_minimum_required(VERSION 3.26)
project(grepy)

set(CMAKE_CXX_STANDARD 17)

add_executable(grepy main.cpp
        logger.cpp
        logger.h
        common.h)
