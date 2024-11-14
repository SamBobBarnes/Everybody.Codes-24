//
// Created by sb17057 on 11/14/2024.
//

#ifndef DAY5_H
#define DAY5_H

#include "../Helpers.h"

using namespace std;

class Day5 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static void printDance(vector<vector<int> > *knights, int height) {
        int width = knights[0].size();

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (knights[0][x].size() > y) {
                    int dancer = knights[0][x][y];
                    cout << dancer;
                } else {
                    cout << " ";
                }
                cout << " ";
            }
            cout << endl;
        }
    }
};

#endif //DAY5_H
