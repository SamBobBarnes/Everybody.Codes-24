//
// Created by sb17057 on 11/24/2024.
//

#ifndef DIRECTION_H
#define DIRECTION_H
#include <string>

enum Direction {
    Up, Down, Left, Right, Forward, Backward
};

struct GrowthPlan {
    explicit GrowthPlan(const std::string &plan) {
        if (char directionChar = plan[0]; directionChar == 'U') direction = Up;
        else if (directionChar == 'D') direction = Down;
        else if (directionChar == 'L') direction = Left;
        else if (directionChar == 'R') direction = Right;
        else if (directionChar == 'F') direction = Forward;
        else if (directionChar == 'B') direction = Backward;

        distance = stoi(plan.substr(1));
    }

    Direction direction;
    int distance;
};

#endif //DIRECTION_H
