//
// Created by Samuel Barnes on 11/16/24.
//

#ifndef DAY7_H
#define DAY7_H

#include <map>

#include "../Helpers.h"

using namespace std;

class Day7 {
public:
    static string Part1();

    static string Part2();

    static string Part3();

    static void GeneratePlans(vector<string> *plans, const map<char, int> &chars, int length,
                              const string &current = "") {
        if (current.length() == length) {
            plans->push_back(current);
            return;
        }

        for (auto pair: chars) {
            if (pair.second > 0) {
                pair.second -= 1;
            }
            GeneratePlans(plans, chars, length, current + pair.first);
            pair.second += 1;
        }
    }
};

#endif //DAY7_H
