//
// Created by Samuel Barnes on 11/11/24.
//

#include <utility>
#include <vector>

#include "Day2.h"

std::vector<std::string> Day2::split(std::string input) {
    std::string temp = std::move(input);
    std::vector<std::string> result{};
    bool finished{false};

    while (!finished) {
        int spaceIndex = temp.find(' ');
        if (spaceIndex == -1) finished = true;
        std::string token = temp.substr(0, spaceIndex);
        if (token.length() != 0) result.push_back(token);
        temp = temp.substr(spaceIndex + 1);
    }

    return result;
}
