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

    vector<int> minCount;
    int max = 0, total = 0;

    for (int i: numbers) {
        max = std::max(max, i);
    }
    minCount.resize(max / 2 + 51);
    for (int x = 1; x < minCount.size(); ++x) {
        int min = Max;
        for (int s: stamps)
            if (x - s >= 0)
                min = std::min(min, minCount[x - s]);
        minCount[x] = min + 1;
    }

    for (int b: numbers) {
        int l = b / 2, h = b - l, min = Max;
        do min = std::min(min, minCount[l--] + minCount[h++]);
        while (h - l <= 100);
        total += min;
    }

    return total;
}
