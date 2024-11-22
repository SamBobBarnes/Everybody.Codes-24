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

    int UpDiff() {
        return diff(up);
    }

    int DownDiff() {
        return diff(down);
    }

    int LeftDiff() {
        return diff(left);
    }

    int RightDiff() {
        return diff(right);
    }

private:
    int diff(Platform *platform) {
        if (platform == nullptr) return -1;
        return getDiff(level, platform->level);
    }

    static int getDiff(const int left, const int right) {
        int diff = abs(left - right);
        if (diff > 5) diff -= diff - 5;
        return diff;
    }
};

#endif //PLATFORM_H
