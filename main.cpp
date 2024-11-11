#include <iostream>

#include "Helpers.h"
#include "Day1/Day1.h"
#include "Day2/Day2.h"

int main() {
    std::cout << "Current dir: " << Helpers::pwd() << std::endl;
    switch (2) {
        case 1:
            std::cout << "Day 1 - Part 1: " << Day1::Part1() << std::endl;
            std::cout << "Day 1 - Part 2: " << Day1::Part2() << std::endl;
            std::cout << "Day 1 - Part 3: " << Day1::Part3() << std::endl;
        case 2:
            std::cout << "Day 2 - Part 1: " << Day2::Part1() << std::endl;
            std::cout << "Day 2 - Part 2: " << Day2::Part2() << std::endl;
            std::cout << "Day 2 - Part 3: " << Day2::Part3() << std::endl;
            break;
        default:
            std::cout << "TILT" << std::endl;
    }
}
