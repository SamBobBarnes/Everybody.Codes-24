#include <algorithm>

#include "Day9.h"
#include "Pair.h"

int Day9::Part3() {
    auto lines = Helpers::readFile(9, 3);
    vector<int> numbers{};
    for (auto &line: lines) {
        numbers.push_back(stoi(line));
    }

    vector<int> stamps{101, 100, 75, 74, 50, 49, 38, 37, 30, 25, 24, 20, 16, 15, 10, 5, 3, 1};

    vector<int> beetleCounts{};

    for (const int &goal: numbers) {
        vector<Pair> pairs{};

        for (int x = 0; x < 50; x++) {
            int left;
            int right;
            if (goal % 2 == 0) {
                left = goal / 2 - x;
                right = goal / 2 + x;
            } else {
                left = goal / 2 - x;
                right = goal / 2 + 1 + x;
            }

            int leftResult;
            int rightResult;
            vector range{1, 2};
            for (int s: range) {
                vector<vector<int> > memo{};
                for (int i = 0; i < stamps.size(); i++) {
                    vector<int> row{};
                    for (int j = 0; j < goal + 1; j++) {
                        row.push_back(-1);
                    }
                    memo.push_back(row);
                }
                int sum;
                if (s == 1) sum = left;
                else sum = right;
                int beetles = minCoins(0, sum, &stamps, &memo);
                if (s == 1) leftResult = beetles;
                else rightResult = beetles;
            }
            pairs.emplace_back(leftResult, rightResult);
        }

        sort(pairs.begin(), pairs.end());

        beetleCounts.push_back(pairs.front().total());
    }

    int total{0};

    for (const int &count: beetleCounts) total += count;

    return total;
}
