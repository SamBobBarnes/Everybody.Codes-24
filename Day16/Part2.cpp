#include <set>

#include "CatFace.h"
#include "Day16.h"

long long Day16::Part2() {
    const auto lines = Helpers::readFile(16, 2);
    vector<int> spinCounts{};
    for (const auto countStrings = Helpers::split(lines[0], ','); auto spin: countStrings) {
        spinCounts.push_back(stoi(spin));
    }

    set<char> symbols{};
    vector<vector<CatFace> > wheels{};
    for (int j = 0; j < spinCounts.size(); ++j) {
        vector<CatFace> wheel{};
        for (int i = 2; i < lines.size(); ++i) {
            if (j * 4 >= lines[i].length()) continue;
            auto row = lines[i].substr(4 * j, 3);
            if (row == "   ") continue;
            wheel.emplace_back(row);
            symbols.insert_range(wheel[wheel.size() - 1].chars2 | views::keys);
        }
        wheels.push_back(wheel);
    }

    const int wheelCount = spinCounts.size();

    vector<int> currentIndex{};
    currentIndex.resize(wheelCount);

    vector<CatFace *> currentFaces{};

    long long rounds = 202420242024;
    long duplicateIndex{0};
    long long total{0};

    for (int i = 1; i <= rounds; ++i) {
        currentFaces.clear();
        for (int j = 0; j < currentIndex.size(); ++j) {
            currentIndex[j] += spinCounts[j];
        } // rotate wheels

        for (int k = 0; k < spinCounts.size(); ++k) {
            int wheelIndex = currentIndex[k] % wheels[k].size();
            currentFaces.push_back(&wheels[k][wheelIndex]);
        } // sets current faces array

        auto currentCounts = GetCounts2(currentFaces); // counts face symbols
        int score{0};
        for (const auto val: currentCounts | views::values) {
            if (val >= 3) {
                score += val - 2;
            }
        } // tallies totals
        total += score;

        bool duplicate{true};
        for (auto j = 0; j < currentIndex.size(); j++) {
            if (currentIndex[j] % wheels[j].size() != 0) {
                duplicate = false;
                break;
            }
        }

        if (duplicate) {
            duplicateIndex = i;
            break;
        } // checks for the first duplicate
    }

    int roundsRemainder = rounds % (duplicateIndex);
    long long duplicateRounds = rounds / (duplicateIndex);

    total *= duplicateRounds;

    currentIndex.clear();
    currentIndex.resize(wheelCount);

    for (int i = 0; i < roundsRemainder; ++i) {
        currentFaces.clear();
        for (int j = 0; j < currentIndex.size(); ++j) {
            currentIndex[j] += spinCounts[j];
        } // rotate wheels

        for (int k = 0; k < spinCounts.size(); ++k) {
            int wheelIndex = currentIndex[k] % wheels[k].size();
            currentFaces.push_back(&wheels[k][wheelIndex]);
        } // sets current faces array

        auto currentCounts = GetCounts2(currentFaces); // counts face symbols
        int score{0};
        for (const auto val: currentCounts | views::values) {
            if (val >= 3) {
                score += val - 2;
            }
        } // tallies totals
        total += score;
    }

    return total;
}
