#include <algorithm>
#include <map>

#include "Day11.h"

long long Day11::Part3() {
    auto lines = Helpers::readFile(11, 3);
    map<string, vector<string> > conversions{};
    vector<string> startingBugs{};
    map<string, long long> population{};
    vector<long long> populationCounts{};

    for (auto &line: lines) {
        auto parts = Helpers::split(line, ':');
        auto parent = parts[0];
        auto offspring = Helpers::split(parts[1], ',');

        vector<string> offspringChars{};
        for (auto child: offspring) {
            offspringChars.push_back(child);
        }
        conversions.insert({parent, offspringChars});
        startingBugs.push_back(parent);
    }

    int rounds{20};

    for (string startingBug: startingBugs) {
        population.insert({startingBug, 1});
        for (int i: views::iota(0, rounds)) {
            map<string, long long> nextGen{};

            for (auto bug: population) {
                for (auto child: conversions[bug.first]) {
                    if (nextGen.count(child) > 0) nextGen[child] += bug.second;
                    else nextGen.insert({child, bug.second});
                }
            }
            population = move(nextGen);
        }
        long long count{0};
        for (auto bug: population) {
            count += bug.second;
        }
        populationCounts.push_back(count);
        population.clear();
    }

    ranges::sort(populationCounts);

    return populationCounts.back() - populationCounts.front();
}
