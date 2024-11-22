#include <algorithm>

#include "Day12.h"

int Day12::Part2() {
    auto lines = Helpers::readFile(12, 2);
    vector<int> catapultHeights{};
    vector<tuple<Point, char> > targets{};

    for (int y = lines.size() - 1; y >= 0; --y) {
        auto line = lines[lines.size() - 1 - y];
        for (int x = 0; x < line.length() - 1; ++x) {
            if (line[x + 1] != '.' && line[x + 1] != 'T' && line[x + 1] != 'H' && line[x + 1] != '=') {
                catapultHeights.push_back(y);
            }
            if (line[x + 1] == 'T' || line[x + 1] == 'H') targets.push_back({{x, y}, line[x + 1]});
        }
    }

    int ranking{0};

    for (auto target: targets) {
        vector<int> rankings{};
        for (auto catapult: catapultHeights) {
            int power = CanHit(catapult, get<0>(target));
            if (power == -1) continue;
            rankings.push_back(power * catapult * (get<1>(target) == 'H' ? 2 : 1));
        }
        ranges::sort(rankings);
        ranking += rankings.front();
    }


    return ranking;
}
