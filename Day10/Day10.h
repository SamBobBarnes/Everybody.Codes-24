#ifndef DAY10_H
#define DAY10_H

#include "../Helpers.h"

using namespace std;

class Day10 {
public:
    static string Part1();

    static int Part2();

    static int Part3();

private:
    static char SearchForMatch(int x, int y, vector<vector<char> > *map);
};

#endif //DAY10_H
