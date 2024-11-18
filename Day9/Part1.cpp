#include "Day9.h"

int Day9::Part1() {
    auto lines = Helpers::readFile(9, 1);
    vector<int> numbers{};
    for (auto &line: lines) {
        numbers.push_back(stoi(line));
    }

    vector<int> beetleCounts{};

    for (const int &goal: numbers) {
        int left = goal;
        int current{0};
        int beetlesUsed{0};
        int tens = left / 10;
        current += tens * 10;
        left = goal - current;
        int fives = left / 5;
        current += fives * 5;
        left = goal - current;
        int threes = left / 3;
        current += threes * 3;
        left = goal - current;
        int ones = left;
        beetlesUsed = ones + threes + fives + tens;
        beetleCounts.push_back(beetlesUsed);
    }

    int total{0};

    for (const int &count: beetleCounts) total += count;

    return total;
}
