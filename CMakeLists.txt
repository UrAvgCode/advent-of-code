cmake_minimum_required(VERSION 3.27)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TBB QUIET)

include_directories(./include)

add_subdirectory(2020)
add_subdirectory(2023)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
