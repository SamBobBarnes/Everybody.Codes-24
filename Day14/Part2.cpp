#include <set>

#include "Day14.h"

int Day14::Part2() {
    auto lines = Helpers::readFile(14, 2);

    set<Point3> uniquePoints{};

    for (auto line: lines) {
        Point3 current{0, 0, 0};
        auto directions = Helpers::split(line, ',');
        for (auto direction: directions) {
            GrowthPlan plan{direction};
            switch (plan.direction) {
                case Up:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.y++;
                        uniquePoints.insert(current);
                    }
                    break;
                case Down:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.y--;
                        uniquePoints.insert(current);
                    }
                    break;
                case Left:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.x--;
                        uniquePoints.insert(current);
                    }
                    break;
                case Right:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.x++;
                        uniquePoints.insert(current);
                    }
                    break;
                case Forward:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.z++;
                        uniquePoints.insert(current);
                    }
                    break;
                case Backward:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.z--;
                        uniquePoints.insert(current);
                    }
                    break;
            }
        }
    }


    return uniquePoints.size();
}
