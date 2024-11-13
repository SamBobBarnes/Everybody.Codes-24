#include <iostream>

#include "Helpers.h"
#include "Day1/Day1.h"
#include "Day2/Day2.h"
#include "Day3/Day3.h"
#include "Day4/Day4.h"


int main() {
    std::cout << "Running on ";
#ifdef _WIN32
    std::cout << "Windows";
#else
    std::cout << "Linux";
#endif
    std::cout << std::endl << std::endl;
    std::cout << "Current dir: " << Helpers::pwd() << std::endl;

    // Helpers::colorReference();

    switch (4) {
        case 1:
            std::cout << "Day 1 - Part 1: " << Day1::Part1() << std::endl;
            std::cout << "Day 1 - Part 2: " << Day1::Part2() << std::endl;
            std::cout << "Day 1 - Part 3: " << Day1::Part3() << std::endl;
        case 2:
            std::cout << "Day 2 - Part 1: " << Day2::Part1() << std::endl;
            std::cout << "Day 2 - Part 2: " << Day2::Part2() << std::endl;
            std::cout << "Day 2 - Part 3: " << Day2::Part3() << std::endl;
            break;
        case 3:
            std::cout << "Day 3 - Part 1: " << Day3::Part1() << std::endl;
            std::cout << "Day 3 - Part 2: " << Day3::Part2() << std::endl;
            std::cout << "Day 3 - Part 3: " << Day3::Part3() << std::endl;
            break;
        case 4:
            std::cout << "Day 4 - Part 1: " << Day4::Part1() << std::endl;
            std::cout << "Day 4 - Part 2: " << Day4::Part2() << std::endl;
            std::cout << "Day 4 - Part 3: " << Day4::Part3() << std::endl;
            break;
        default:
            std::cout << "TILT" << std::endl;
    }
}
