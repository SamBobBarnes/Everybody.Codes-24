//
// Created by Samuel Barnes on 11/16/24.
//

#ifndef PLAN_H
#define PLAN_H
#include <string>
#include <vector>
#include "../Helpers.h"

struct Plan {
    explicit Plan(const std::string &label, const std::string &plan) {
        this->label = label;
        for (int i = 0; i < plan.length(); i++) {
            steps.push_back(plan[i]);
        }
    }

    explicit Plan(const std::string &line) {
        label = Helpers::split(line, ':')[0];
        auto stepStrings = Helpers::split(Helpers::split(line, ':')[1], ',');
        for (auto &step: stepStrings) {
            steps.push_back(step[0]);
        }
    }

    explicit Plan(string *line);

    std::string label{};
    std::vector<char> steps{};
    int currentIndex{-1};
    int total{0};

    char next() {
        currentIndex++;
        if (currentIndex == steps.size()) currentIndex = 0;
        return steps[currentIndex];
    }

    bool operator<(const Plan &other) const {
        return total > other.total;
    }
};

#endif //PLAN_H
