#ifndef DAY16_H
#define DAY16_H

#include "CatFace.h"
#include "../Helpers.h"

using namespace std;

class Day16 {
public:
    static string Part1();

    static long long Part2();

    static int Part3();

    static map<char, int> GetCounts2(const vector<CatFace *> &row) {
        map<char, int> counts{};

        for (const CatFace *cat: row) {
            for (auto [fst, snd]: cat->chars2) {
                counts[fst] += snd;
            }
        }

        return counts;
    }

    static void GenerateCombinations(vector<vector<CatFace> > *wheels, set<vector<int> > *faceCombos,
                                     const vector<int> &currentCombo = {},
                                     int index = 0);
};

#endif //DAY16_H
