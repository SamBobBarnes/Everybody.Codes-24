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

    static int Count(const vector<char> *l, const char x) {
        int total{0};
        for (int i = 0; i < l->size(); ++i) {
            if (l[0][i] == x)total++;
        }
        return total;
    }

    static int Count(const string *l, const char x) {
        int total{0};
        for (int i = 0; i < l->size(); ++i) {
            if (l[0][i] == x)total++;
        }
        return total;
    }

    static bool ValidWord(const string *word) {
        return Count(word,'?') == 0;
    }

private:
    static int CalculatePower(string word);

    static char SearchForMatch(int x, int y, vector<vector<char> > *map);

    static char SearchForMatch3(int x, int y, const vector<string> *map, const Point *origin);
};

#endif //DAY10_H
