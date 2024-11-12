#include <ranges>

#include "Day2.h"
//
// Created by Samuel Barnes on 11/12/24.
//
std::vector<std::vector<bool> > Day2::pointsToIntMap(const std::vector<Point> &points, const int w, const int h) {
    std::vector<std::vector<bool> > map{};
    for (int i: std::views::iota(0, w)) {
        std::vector<bool> subMap{};
        for (int j: std::views::iota(0, h)) {
            subMap.push_back(false);
        }
        map.push_back(subMap);
    }

    for (const auto &point: points) {
        map[point.x][point.y] = true;
    }
    return map;
}

std::vector<std::vector<bool> > Day2::orMap(std::vector<std::vector<bool> > map1, std::vector<std::vector<bool> > map2,
                                            const int w, const int h) {
    std::vector<std::vector<bool> > map{};

    for (int i: std::views::iota(0, w)) {
        std::vector<bool> subMap{};
        for (int j: std::views::iota(0, h)) {
            subMap.push_back(map1[i][j] || map2[i][j]);
        }
        map.push_back(subMap);
    }

    return map;
}

int Day2::countPoints(std::vector<std::vector<bool> > map, int w, int h) {
    int result{0};
    for (int i: std::views::iota(0, w)) {
        for (int j: std::views::iota(0, h)) {
            if (map[i][j]) result++;
        }
    }
    return result;
}

