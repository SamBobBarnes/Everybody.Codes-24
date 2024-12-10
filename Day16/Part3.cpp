#include <set>

#include "CatFace.h"
#include "Day16.h"

int Day16::Part3() {
    const auto lines = Helpers::readFile(16, 3);

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

    long long rounds = 256;
    long long total{0};

    set<vector<CatFace *> > faceCombos{};


    return 0;
}
