#include <iostream>
#include "Day1/Day1.h"
#include "Day2/Day2.h"

int main() {
    const int day = 2;
    switch (day) {
        case 1:
            std::cout << "Day 1 - Part 1: " << Day1::Part1() << std::endl;
            std::cout << "Day 1 - Part 2: " << Day1::Part2() << std::endl;
            std::cout << "Day 1 - Part 3: " << Day1::Part3() << std::endl;
            break;
        case 2:
            std::cout << "Day 2 - Part 1: " << Day2::Part1() << std::endl;
        // std::cout << "Day 2 - Part 2: " << Day2::Part2() << std::endl;
        // std::cout << "Day 2 - Part 3: " << Day2::Part3() << std::endl;
            break;
        default:
            std::cout << "TILT" << std::endl;
    }
}
