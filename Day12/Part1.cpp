#include <algorithm>

#include "Day12.h"
#include "../Point.h"

int GetLandingDistance(int height, int power) {
    return power * 3 + height - 1;
}

int GetPower(int distance) {
    double power = distance / 3.0;
    if (floor(power) == power) return power;
    return -1;
}

int CanHit(int height, Point target) {
    int distance = target.x - (height - target.y);
    return GetPower(distance);
}

int Day12::Part1() {
    auto lines = Helpers::readFile(12, 1);

    vector<int> catapultHeights{};
    vector<Point> targets{};

    for (int y = lines.size() - 1; y >= 0; --y) {
        auto line = lines[lines.size() - 1 - y];
        for (int x = 0; x < line.length() - 1; ++x) {
            if (line[x + 1] != '.' && line[x + 1] != 'T' && line[x + 1] != '=') {
                catapultHeights.push_back(y);
            }
            if (line[x + 1] == 'T') targets.emplace_back(x, y);
        }
    }

    int ranking{0};

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
