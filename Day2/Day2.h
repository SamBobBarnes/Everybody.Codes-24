//
// Created by Samuel Barnes on 11/10/24.
//
#pragma once

#include <vector>

#include "FindResult.h"
#include "../Helpers.h"

#ifndef DAY2_H
#define DAY2_H

class Day2 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static std::vector<std::string> split(std::string input);

    static FindResult findWordOnGrid(int w, int h, char *grid, const std::string &wordToFind);

    static std::vector<std::vector<bool> > pointsToIntMap(const std::vector<Point> &points, int w, int h);

    static std::vector<std::vector<bool> > orMap(std::vector<std::vector<bool> > map1,
                                                 std::vector<std::vector<bool> > map2, int w, int h);

    static int countPoints(std::vector<std::vector<bool> > map, int w, int h);

    static std::vector<std::vector<bool> > createMap(int w, int h);

    static void printMap(const std::vector<std::vector<bool> > *map, char *grid);

private:
    static std::string reverse(std::string word) {
        std::string reverseWord;
        for (int i = word.length() - 1; i >= 0; i--) {
            reverseWord.push_back(word[i]);
        }

        return reverseWord;
    }

    static char getChar(int width, const char *grid, int x, int y) {
        return *((grid + y * width) + x);
    }
};
#endif //DAY2_H
