//
// Created by Samuel Barnes on 11/16/24.
//

#include "Day7.h"
#include "Plan.h"

string Day7::Part1() {
    auto lines = Helpers::readFile(7, 1);

    vector<Plan> plans{};

    for (std::string &line: lines) {
        Plan temp{line};
        plans.push_back(temp);
    }

    return "";
}
