//
// Created by sb17057 on 11/11/2024.
//

#ifndef FINDRESULT_H
#define FINDRESULT_H
#include <iosfwd>
#include <ostream>
#include <string>
#include <utility>
#include <vector>


struct Point {
    Point(const int x, const int y) {
        this->x = x;
        this->y = y;
    }

    [[nodiscard]] bool equals(const Point &b) const {
        return this->x == b.x && this->y == b.y;
    }

    bool operator<(const Point &other) const {
        if (y == other.y) return x < other.x;
        return y < other.y;
    }

    int x;
    int y;
};

struct FindResult {
    explicit FindResult(const bool found, std::vector<Point> symbolLocations) {
        this->found = found;
        this->symbolLocations = std::move(symbolLocations);
    }

    bool found;
    std::vector<Point> symbolLocations;
};


#endif //FINDRESULT_H
