cmake_minimum_required(VERSION 3.29)
project(Everybody_Codes_24)

set(CMAKE_CXX_STANDARD 23)

add_executable(Everybody_Codes_24 main.cpp
        Day1/Day1.cpp
        Day1/Day1.h
        Day2/Day2.h
        Day2/Part1.cpp
        Day2/Split.cpp
        Day2/Part2.cpp
        Helpers.h
        Day2/Part3.cpp
        Day2/findWordOnGrid.cpp
        Day2/FindResult.h
        Day2/PointsToIntMap.cpp)

add_subdirectory(tests)