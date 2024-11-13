//
// Created by sb17057 on 11/11/2024.
//

#ifndef FINDRESULT_H
#define FINDRESULT_H
#include <ostream>
#include <utility>
#include <vector>
#include "../Point.h"

struct FindResult {
    explicit FindResult(const bool found, std::vector<Point> symbolLocations) {
        this->found = found;
        this->symbolLocations = std::move(symbolLocations);
    }

    bool found;
    std::vector<Point> symbolLocations;
};


#endif //FINDRESULT_H
