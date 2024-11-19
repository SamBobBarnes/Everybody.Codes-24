#include "Day10.h"

char Day10::SearchForMatch(const int x, const int y, vector<vector<char> > *map) {
    vector<char> tb{};
    vector<char> lr{};
    for (int my = 0; my < 8; ++my) {
        if (my > 1 && my < 6) continue;
        tb.push_back(map[0][my][x]);
    }
    for (int mx = 0; mx < 8; ++mx) {
        if (mx > 1 && mx < 6) continue;
        lr.push_back(map[0][y][mx]);
    }

    for (char i: tb)
        if (ranges::find(lr, i) != lr.end()) return i;
    return 0;
}

string Day10::Part1() {
    auto lines = Helpers::readFile(10, 1);
    vector<vector<char> > map{};

    for (int y = 0; y < lines.size(); y++) {
        vector<char> row{};
        for (int x = 0; x < lines[0].length(); x++) {
            row.push_back(lines[y][x]);
        }
        map.push_back(row);
    }

    string word;
    for (int y = 2; y < 6; ++y) {
        for (int x = 2; x < 6; ++x) {
            word += SearchForMatch(x, y, &map);
        }
    }

    return word;
}
