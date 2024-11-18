#include "Day9.h"

int Day9::Part1() {
    auto lines = Helpers::readFile(9, 1);
    vector<int> numbers{};
    for (auto &line: lines) {
        numbers.push_back(stoi(line));
    }

    vector<int> beetleCounts{};

    for (const int &goal: numbers) {
        int current{0};
        int beetlesUsed{0};
        int tens = (goal - current) / 10;
        current += tens * 10;
        int fives = (goal - current) / 5;
        current += fives * 5;
        int threes = (goal - current) / 3;
        current += threes * 3;
        int ones = (goal - current);
        beetlesUsed = ones + threes + fives + tens;
        beetleCounts.push_back(beetlesUsed);
    }

    int total{0};

    for (const int &count: beetleCounts) total += count;

    return total;
}
