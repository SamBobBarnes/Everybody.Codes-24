//
// Created by sb17057 on 11/11/2024.
//
#include "Day2.h"
#include "FindResult.h"

char getChar(int h, char *grid, int x, int y) {
    return *((grid + y * h) + x);
}

FindResult Day2::findWordOnGrid(const int w, const int h, char *grid, const std::string &wordToFind) {
    FindResult result{false, {}};
    int length = wordToFind.length();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            char current = getChar(h, grid, x, y);
            if (wordToFind[0] == getChar(h, grid, x, y)) {
                // look to right
                std::vector<Point> tempLocations{{x, y}};
                for (int i = 1; i < length; i++) {
                    if (wordToFind[i] != getChar(h, grid, x + i, y)) break;

                    tempLocations.emplace_back(x + i, y);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                    }
                }

                // look to the left
                for (int i = 1; i < length; i++) {
                    if (wordToFind[i] != getChar(h, grid, x - i, y)) break;

                    tempLocations.emplace_back(x - i, y);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                    }
                }
            }
        }
    }

    return result;
}