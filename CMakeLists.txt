cmake_minimum_required(VERSION 3.13)
project (argsParser)
set(CMAKE_CXX_STANDARD 17)

add_library(argsParser STATIC)
enable_testing()

add_subdirectory(tests)

target_sources(argsParser PRIVATE
    include/argsParser.h
    src/argsParser.cpp
)

target_include_directories(argsParser PRIVATE include)
