#include <algorithm>
#include <map>

#include "Day9.h"

int Day9::minCoins(int i, int sum, vector<int> *coins, vector<vector<int> > *memo) {
    if (sum == 0) return 0;
    if (sum < 0 || i == coins->size()) return 10000;

    if (memo[0][i][sum] != -1) return memo[0][i][sum];


    int take = 10000;

    if (coins[0][i] > 0) {
        take = minCoins(i, sum - coins[0][i], coins, memo);
        if (take != 10000) take++;
    }

    int noTake = minCoins(i + 1, sum, coins, memo);

    memo[0][i][sum] = min(take, noTake);
    return memo[0][i][sum];
}

int Day9::Part2() {
    auto lines = Helpers::readFile(9, 2);
    vector<int> numbers{};
    for (auto &line: lines) {
        numbers.push_back(stoi(line));
    }

    vector<int> stamps{30, 25, 24, 20, 16, 15, 10, 5, 3, 1};

    vector<int> beetleCounts{};

    for (const int &goal: numbers) {
        vector<vector<int> > memo{};
        for (int i = 0; i < stamps.size(); i++) {
            vector<int> row{};
            for (int j = 0; j < goal + 1; j++) {
                row.push_back(-1);
            }
            memo.push_back(row);
        }
        int beetles = minCoins(0, goal, &stamps, &memo);
        beetleCounts.push_back(beetles != 10000 ? beetles : -1);
    }

    int total{0};

    for (const int &count: beetleCounts) total += count;

    return total;
}
