//
// Created by sb17057 on 11/13/2024.
//

#ifndef POINT_H
#define POINT_H

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

    bool operator>(const Point &other) const {
        if (x == other.x) return y > other.y;
        return x > other.x;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y > other.y;
    }

    int x;
    int y;
};

#endif //POINT_H
