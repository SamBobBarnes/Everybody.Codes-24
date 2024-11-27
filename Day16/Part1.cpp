#include <set>

#include "CatFace.h"
#include "Day16.h"

map<char, int> GetCounts(vector<CatFace *> row) {
    map<char, int> counts{};

    for (const CatFace *cat: row) {
        for (auto [fst, snd]: cat->chars) {
            counts[fst] += snd;
        }
    }

    return counts;
}

string Day16::Part1() {
    const auto lines = Helpers::readFile(16, 1);
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
            symbols.insert_range(wheel[wheel.size() - 1].chars | views::keys);
        }
        wheels.push_back(wheel);
    }

    const int wheelCount = spinCounts.size();

    vector<int> currentIndex{};
    currentIndex.resize(wheelCount);

    vector<CatFace *> currentFaces{};

    int rounds = 100;
    int total{0};

    for (int i = 0; i < rounds; ++i) {
        currentFaces.clear();
        for (int j = 0; j < currentIndex.size(); ++j) {
            currentIndex[j] += spinCounts[j];
        }

        for (int k = 0; k < spinCounts.size(); ++k) {
            currentFaces.push_back(&wheels[k][currentIndex[k] % wheels[k].size()]);
        }
        auto currentCounts = GetCounts(currentFaces);
        int score{0};
        for (const auto val: currentCounts | views::values) {
            if (val >= 3) {
                score += val - 2;
            }
        }
        total += score;
    }
    string finalRow;

    for (int i = 0; i < currentFaces.size(); ++i) {
        finalRow += currentFaces[i]->face + " ";
    }

    return finalRow.substr(0, finalRow.length() - 1);
}
