#include <ranges>
#include <utility>

#include "Day2.h"
//
// Created by Samuel Barnes on 11/12/24.
//
std::vector<std::vector<bool> > Day2::pointsToIntMap(const std::vector<Point> &points, const int w, const int h) {
    std::vector<std::vector<bool> > map = createMap(w, h);

    for (const auto &point: points) {
        map[point.x][point.y] = true;
    }
    return map;
}

std::vector<std::vector<bool> > Day2::orMap(std::vector<std::vector<bool> > map1, std::vector<std::vector<bool> > map2,
                                            const int w, const int h) {
    std::vector<std::vector<bool> > map = createMap(w, h);

    for (int x: std::views::iota(0, w)) {
        for (int y: std::views::iota(0, h)) {
            if (map1[x][y] || map2[x][y])
                map[x][y] = true;
        }
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

std::vector<std::vector<bool> > Day2::createMap(int w, int h) {
    std::vector<std::vector<bool> > map{};
    map.resize(w);
    for (int x: std::views::iota(0, w)) {
        std::vector<bool> subMap{};
        subMap.resize(h);
        map[x] = subMap;
    }

    return map;
}

void Day2::printMap(const std::vector<std::vector<bool> > *map, char *grid) {
    int width = map->size();
    int height = map[0][0].size();

    std::cout << std::endl;
    for (int y: std::views::iota(0, height)) {
        for (int x: std::views::iota(0, width)) {
            if (map[0][x][y]) std::cout << "\033[31;4m";
            else std::cout << "\033[0m";
            std::cout << getChar(width, grid, x, y);
        }
        std::cout << std::endl;
    }
}
