//
// Created by sb17057 on 11/22/2024.
//

#ifndef PLATFORM_H
#define PLATFORM_H

#include <cmath>

#include "../Point.h"

struct Platform {
    explicit Platform(const int x, const int y, const int height): position(x, y), level(height) {
    }

    Point position;
    int level;

    Platform *up{nullptr};
    Platform *down{nullptr};
    Platform *left{nullptr};
    Platform *right{nullptr};

    vector<tuple<Platform *, int> > GetNeighbors() {
        vector<tuple<Platform *, int> > neighbors{};

        if (UpDiff() >= 0) neighbors.emplace_back(up, UpDiff());
        if (RightDiff() >= 0) neighbors.emplace_back(right, RightDiff());
        if (DownDiff() >= 0) neighbors.emplace_back(down, DownDiff());
        if (LeftDiff() >= 0) neighbors.emplace_back(left, LeftDiff());

        return neighbors;
    }

    int UpDiff() const {
        return diff(up);
    }

    int DownDiff() const {
        return diff(down);
    }

    int LeftDiff() const {
        return diff(left);
    }

    int RightDiff() const {
        return diff(right);
    }

    bool operator<(const Platform &other) const {
        return position < other.position;
    }

    bool operator>(const Platform &other) const {
        return position > other.position;
    }

    bool operator==(const Platform &other) const {
        return position == other.position;
    }

    int diff(const Platform *platform) const {
        if (platform == nullptr) return -1;
        return getDiff(level, platform->level);
    }

    static int getDiff(const int left, const int right) {
        int diff = abs(left - right);
        if (diff > 5) diff = 5 - (diff - 5);
        return diff + 1;
    }
};

struct PlatformDistance {
    explicit PlatformDistance(Platform *platform, const int dist): pointer(platform), distance(dist) {
    }

    Platform *pointer;
    int distance;

    bool operator<(const PlatformDistance &other) const {
        return distance < other.distance;
    }

    bool operator>(const PlatformDistance &other) const {
        return distance > other.distance;
    }
};

#endif //PLATFORM_H
