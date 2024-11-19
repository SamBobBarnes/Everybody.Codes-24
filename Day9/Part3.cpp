#include <algorithm>

#include "Day9.h"
#include "Pair.h"

int Day9::minCoins2(int sum, vector<int> *coins) {
    vector<int> dp{};
    for (int i = 0; i < sum + 1; i++) dp.push_back(Max);
    dp[0] = 0;

    for (int i = coins->size() - 1; i >= 0; i--) {
        for (int j = 1; j <= sum; j++) {
            int take = Max;
            int noTake = Max;

            if (j - coins[0][i] >= 0 && coins[0][i] > 0) {
                take = dp[j - coins[0][i]];
                if (take != Max)take++;
            }
            if (i + 1 < coins->size())
                noTake = dp[j];

            dp[j] = min(take, noTake);
        }
    }

    if (dp[sum] != Max)return dp[sum];
    return -1;
}


int Day9::Part3() {
    auto lines = Helpers::readFile(9, 3);
    vector<int> numbers{};
    for (auto &line: lines) {
        numbers.push_back(stoi(line));
    }

    vector<int> stamps{1, 3, 5, 10, 15, 16, 20, 24, 25, 30, 37, 38, 49, 50, 74, 75, 100, 101};

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
                int sum;
                if (s == 1) sum = left;
                else sum = right;
                int beetles = minCoins2(sum, &stamps);
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
