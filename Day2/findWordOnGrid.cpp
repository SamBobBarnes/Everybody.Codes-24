//
// Created by sb17057 on 11/11/2024.
//
#include <algorithm>

#include "Day2.h"
#include "FindResult.h"
#include <set>

FindResult Day2::findWordOnGrid(const int w, const int h, char *grid, const std::string &wordToFind) {
    FindResult result{false, {}};
    int length = wordToFind.length();

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (wordToFind[0] == getChar(w, grid, x, y)) {
                std::vector<Point> tempLocations{{x, y}};

                if (length == 1) {
                    result.found = true;
                    result.symbolLocations.emplace_back(x, y);
                }

                // look to right
                for (int i = 1; i < length; i++) {
                    int xi = x + i;
                    if (xi >= w) xi -= w;
                    if (wordToFind[i] != getChar(w, grid, xi, y)) {
                        tempLocations = {{x, y}};
                        break;
                    }

                    tempLocations.emplace_back(xi, y);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                        tempLocations = {{x, y}};
                    }
                }

                // look to the left
                for (int i = 1; i < length; i++) {
                    int xi = x - i;
                    if (xi < 0) xi += w;
                    if (wordToFind[i] != getChar(w, grid, xi, y)) {
                        tempLocations = {{x, y}};
                        break;
                    }

                    tempLocations.emplace_back(xi, y);
                    if (i == length - 1) {
                        result.found = true;
                        result.symbolLocations.append_range(tempLocations);
                        tempLocations = {{x, y}};
                    }
                }

                // look down
                if (y <= h - length) {
                    for (int i = 1; i < length; i++) {
                        if (wordToFind[i] != getChar(w, grid, x, y + i)) {
                            tempLocations = {{x, y}};
                            break;
                        }

                        tempLocations.emplace_back(x, y + i);
                        if (i == length - 1) {
                            result.found = true;
                            result.symbolLocations.append_range(tempLocations);
                            tempLocations = {{x, y}};
                        }
                    }
                }
                // look up
                if (y >= length - 1) {
                    for (int i = 1; i < length; i++) {
                        if (wordToFind[i] != getChar(w, grid, x, y - i)) {
                            tempLocations = {{x, y}};
                            break;
                        }

                        tempLocations.emplace_back(x, y - i);
                        if (i == length - 1) {
                            result.found = true;
                            result.symbolLocations.append_range(tempLocations);
                            tempLocations = {{x, y}};
                        }
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
