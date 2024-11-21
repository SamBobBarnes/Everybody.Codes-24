#include <map>

#include "Day11.h"

int Day11::Part1() {
    auto lines = Helpers::readFile(11, 1);
    map<char, vector<char> > conversions{};
    vector<char> population{'A'};

    for (auto &line: lines) {
        auto parts = Helpers::split(line, ':');
        auto parent = parts[0];
        auto offspring = Helpers::split(parts[1], ',');

        vector<char> offspringChars{};
        for (auto child: offspring) {
            offspringChars.push_back(child[0]);
        }
        conversions.insert({parent[0], offspringChars});
    }

    int rounds{4};

    for (int i: views::iota(0, rounds)) {
        vector<char> nextGen{};

        for (char bug: population) {
            nextGen.append_range(conversions[bug]);
        }
        population = move(nextGen);
    }

    return population.size();
}