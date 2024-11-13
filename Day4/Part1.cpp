//
// Created by sb17057 on 11/13/2024.
//

#include "Day4.h"

int Day4::Part1() {
    auto lines = Helpers::readFile("Day4/Part1.txt");
    vector<int> nails{};

    int min{0};

    for (const auto &line: lines) {
        int nail = std::stoi(line);
        if (min == 0 || nail < min) min = nail;
        nails.push_back(nail);
    }

    int total{0};
    for (int nail: nails) {
        total += nail - min;
    }

    return total;
}
