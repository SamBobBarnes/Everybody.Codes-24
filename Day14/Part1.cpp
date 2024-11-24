#include "Day14.h"
#include "direction.h"

int Day14::Part1() {
    auto lines = Helpers::readFile(14, 1);
    auto directions = Helpers::split(lines[0], ',');
    vector<GrowthPlan> plans{};

    for (auto direction: directions) {
        if (direction[0] != 'U' && direction[0] != 'D') continue;
        plans.emplace_back(direction);
    }

    int current{0};
    int max{0};

    for (auto plan: plans) {
        if (plan.direction == Direction::Up) current += plan.distance;
        else current -= plan.distance;

        if (current > max) max = current;
    }

    return max;
}
