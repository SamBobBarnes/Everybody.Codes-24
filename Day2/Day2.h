//
// Created by Samuel Barnes on 11/10/24.
//
#pragma once

#include <vector>
#include "../Helpers.h"

#ifndef DAY2_H
#define DAY2_H

class Day2 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static std::vector<std::string> split(std::string input);

private:
    static std::string reverse(std::string word) {
        std::string reverseWord;
        for (int i = word.length() - 1; i >= 0; i--) {
            reverseWord.push_back(word[i]);
        }

        return reverseWord;
    }
};
#endif //DAY2_H
