#ifndef DAY9_H
#define DAY9_H

#include "../Helpers.h"

using namespace std;

class Day9 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static int minCoins(int i, int sum, vector<int> *coins, vector<vector<int> > *memo);
};

#endif //DAY9_H
