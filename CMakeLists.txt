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
        Day2/PointsToIntMap.cpp
        Day3/Day3.h
        Day3/Part1.cpp
        Point.h
        Day3/Part2.cpp
        Day3/Part3.cpp
        Day4/Day4.h
        Day4/Part1.cpp
        Day4/Part2.cpp
        Day4/Part3.cpp
        Day5/Day5.h
        Day5/Part1.cpp
        Day5/Part2.cpp
        Day5/Part3.cpp
        Day5/Bucket.h
        Day6/Day6.h
        Day6/Part1.cpp
        Day6/Part2.cpp
        Day6/Part3.cpp
        Day6/Node.h
        Day7/Part1.cpp
        Day7/Part2.cpp
        Day7/Part3.cpp
        Day7/Day7.h
        Day7/Plan.h
)

add_subdirectory(tests)