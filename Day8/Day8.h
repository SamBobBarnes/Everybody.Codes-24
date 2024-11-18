#ifndef DAY8_H
#define DAY8_H

#include "../Helpers.h"

using namespace std;

class Day8 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static int WidthOfTower(const int height) {
        return 1 + 2 * (height - 1);
    }
};

#endif //DAY8_H
