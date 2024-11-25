//
// Created by sb17057 on 11/25/2024.
//

#ifndef GARDENPOINT_H
#define GARDENPOINT_H

#include "../Point.h"

struct GardenPoint : Point {
    GardenPoint(const int x, const int y, const bool impasse, const bool herb, const char tileChar): Point(x, y),
        impasse(impasse), herb(herb), tileChar(tileChar) {
    }

    GardenPoint *parent = nullptr;
    bool impasse{true};
    bool herb{false};
    char tileChar;
};

#endif //GARDENPOINT_H
