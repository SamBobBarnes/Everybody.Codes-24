#include <set>

#include "CatFace.h"
#include "Day16.h"

map<char, int> GetCounts2(vector<CatFace *> row) {
    map<char, int> counts{};

    for (const CatFace *cat: row) {
        for (auto [fst, snd]: cat->chars2) {
            counts[fst] += snd;
        }
    }

    return counts;
}

int Day16::Part2() {
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
    vector<string> indexHistory{};

    long rounds = 202420242024;
    long duplicateIndex{0};
    long total{0};

    for (int i = 0; i < rounds; ++i) {
        currentFaces.clear();
        string currentIndexString;
        for (int j = 0; j < currentIndex.size(); ++j) {
            currentIndex[j] += spinCounts[j];
        }

        for (int k = 0; k < spinCounts.size(); ++k) {
            int wheelIndex = currentIndex[k] % wheels[k].size();
            currentIndexString += to_string(wheelIndex);
            currentFaces.push_back(&wheels[k][wheelIndex]);
        }

        if (ranges::find(indexHistory, currentIndexString) != indexHistory.end()) {
            duplicateIndex = i;
            break;
        }

        auto currentCounts = GetCounts2(currentFaces);
        int score{0};
        for (const auto val: currentCounts | views::values) {
            if (val >= 3) {
                score += val - 2;
            }
        }
        total += score;

        indexHistory.push_back(currentIndexString);
    }

    int roundsRemainder = rounds % (duplicateIndex - 1);
    int duplicateRounds = rounds / (duplicateIndex - 1);

    total *= duplicateRounds;

    for (int j = 0; j < currentIndex.size(); ++j) {
        currentIndex[j] -= spinCounts[j];
    }

    for (int i = 0; i < roundsRemainder; ++i) {
        currentFaces.clear();
        string currentIndexString;
        for (int j = 0; j < currentIndex.size(); ++j) {
            currentIndex[j] += spinCounts[j];
        }

        for (int k = 0; k < spinCounts.size(); ++k) {
            int wheelIndex = currentIndex[k] % wheels[k].size();
            currentIndexString += to_string(wheelIndex);
            currentFaces.push_back(&wheels[k][wheelIndex]);
        }

        if (ranges::find(indexHistory, currentIndexString) != indexHistory.end()) {
            duplicateIndex = i;
            break;
        }

        auto currentCounts = GetCounts2(currentFaces);
        int score{0};
        for (const auto val: currentCounts | views::values) {
            if (val >= 3) {
                score += val - 2;
            }
        }
        total += score;

        indexHistory.push_back(currentIndexString);
    }

    return total;
}
