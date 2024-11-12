//
// Created by sb17057 on 11/11/2024.
//
#include <algorithm>

#include "Day2.h"
#include "FindResult.h"
#include <set>

char getChar(int width, char *grid, int x, int y) {
    return *((grid + y * width) + x);
}

FindResult Day2::findWordOnGrid(const int w, const int h, char *grid, const std::string &wordToFind) {
    FindResult result{false, {}};
    int length = wordToFind.length();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (wordToFind[0] == getChar(w, grid, x, y)) {
                // look to right
                std::vector<Point> tempLocations{{x, y}};
                for (int i = 1; i < length; i++) {
                    int xi = x + i;
                    if (xi >= w) xi -= w;
                    if (wordToFind[i] != getChar(w, grid, xi, y)) break;

                    tempLocations.emplace_back(xi, y);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                    }
                }
                // look to the left
                for (int i = 1; i < length; i++) {
                    int xi = x - i;
                    if (xi < 0) xi += w;
                    if (wordToFind[i] != getChar(w, grid, xi, y)) break;

                    tempLocations.emplace_back(xi, y);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                    }
                }
                // look down
                for (int i = 1; i < length; i++) {
                    if (wordToFind[i] != getChar(w, grid, x, y + i)) break;

                    tempLocations.emplace_back(x, y + i);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                    }
                }
                // look up
                for (int i = 1; i < length; i++) {
                    if (wordToFind[i] != getChar(w, grid, x, y - i)) break;

                    tempLocations.emplace_back(x, y - i);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                    }
                }
            }
        }
    }

    //Remove duplicates
    sort(result.symbolLocations.begin(), result.symbolLocations.end());
    std::set<Point> s(result.symbolLocations.begin(), result.symbolLocations.end());
    result.symbolLocations.assign(s.begin(), s.end());

    return result;
}
