//
// Created by sb17057 on 11/13/2024.
//

#ifndef DAY4_H
#define DAY4_H

#include "../Helpers.h"
using namespace std;

class Day4 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

private:
    static std::string leftpad(const std::string &str, int width, char fill = ' ') {
        if (str.length() >= width) {
            return str;
        }

        return std::string(width - str.length(), fill) + str;
    }
};
#endif //DAY4_H
