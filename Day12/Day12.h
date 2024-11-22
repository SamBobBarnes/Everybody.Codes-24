#ifndef DAY12_H
#define DAY12_H

#include "../Helpers.h"
#include "../Point.h"

using namespace std;

class Day12 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static int GetLandingDistance(int height, int power) {
        return power * 3 + height - 1;
    }

    static int GetPower(int distance) {
        double power = distance / 3.0;
        if (floor(power) == power) return power;
        return -1;
    }

    static int CanHit(int height, Point target) {
        int distance = target.x - (height - target.y);
        return GetPower(distance);
    }
};

#endif //DAY12_H
