//
// Created by sb17057 on 11/25/2024.
//

#ifndef GARDENPOINT_H
#define GARDENPOINT_H

#include "../Point.h"

struct GardenPoint : Point {
    GardenPoint(const int x, const int y, const bool bush, const bool herb): Point(x, y), bush(bush), herb(herb) {
    }

    GardenPoint *parent = nullptr;
    bool bush{true};
    bool herb{false};
};

#endif //GARDENPOINT_H
