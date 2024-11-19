#ifndef DAY10_H
#define DAY10_H

#include "../Helpers.h"
#include "../Point.h"

using namespace std;

class Day10 {
public:
    static string Part1();

    static int Part2();

    static int Part3();

private:
    static int CalculatePower(string word);
    static char SearchForMatch(int x, int y, vector<vector<char> > *map);

    static char SearchForMatch3(int x, int y, const vector<string> *map, const Point *origin);
};

#endif //DAY10_H
