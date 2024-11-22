#include <algorithm>

#include "Day12.h"

int Day12::Part3() {
    auto lines = Helpers::readFile(12, 3);
    vector<int> catapultHeights{3, 2, 1};
    vector<Point> targets{};

    for (auto line: lines) {
        auto coords = Helpers::split(line, ' ');
        targets.emplace_back(stoi(coords[0]), stoi(coords[1]) + 1);
    }

    int ranking{0};

    cout << CanHit(1, {2, 3}) << endl;

    for (auto target: targets) {
        vector<int> rankings{};
        for (auto catapult: catapultHeights) {
            int power = CanHit(catapult, target);
            if (power == -1) continue;
            rankings.push_back(power * catapult);
        }
        ranges::sort(rankings);
        ranking += rankings.front();
    }


    return ranking;
}
