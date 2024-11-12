#include "Day2.h"
//
// Created by Samuel Barnes on 11/12/24.
//
std::vector<std::vector<bool> > Day2::pointsToIntMap(std::vector<Point> points, const int w, const int h) {
    std::vector<std::vector<bool> > map();
    for (const auto &point: points) {
        map[point.x][point.y] = true;
    }
    return map;
}
