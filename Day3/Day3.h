//
// Created by sb17057 on 11/13/2024.
//

#ifndef DAY3_H
#define DAY3_H

#include "../Helpers.h"
using namespace std;

const char alert[] = "\033[31;4m";
const char info[] = "\033[34m";
const char underline[] = "\003[4m";
const char reset[] = "\033[0m";

class Day3 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static void PrintMap(const std::vector<std::vector<int> > *map) {
        vector<string> colors{
            "\033[0m",
            "\033[94m", "\033[34m", "\033[96m", "\033[93m",
            "\033[33m", "\033[92m", "\033[32m", "\033[95m",
            "\033[35m", "\033[91m", "\033[31m", "\033[94m",
            "\033[34m", "\033[96m", "\033[93m", "\033[33m",
            "\033[92m", "\033[32m", "\033[95m", "\033[35m",
            "\033[91m", "\033[31m"
        };

        int height = map[0].size();
        int width = map[0][0].size();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int hole = map[0][y][x];
                cout << (hole > 0 ? colors[hole] : reset);
                cout << hole;
            }
            cout << endl;
        }
    }
};


#endif //DAY3_H
