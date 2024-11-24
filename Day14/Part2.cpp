#include <set>

#include "Day14.h"

int Day14::Part2() {
    auto lines = Helpers::readFile(14, 2);
    vector<vector<GrowthPlan> > plans{};

    set<Point> uniquePoints{};

    for (auto line: lines) {
        Point3 current{0, 0, 0};
        auto directions = Helpers::split(lines[0], ',');
        for (auto direction: directions) {
            GrowthPlan plan{direction};
        }
    }


    return 0;
}
