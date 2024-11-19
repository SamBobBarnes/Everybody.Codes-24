#include <map>

#include "Day10.h"
#include "../Point.h"

char Day10::SearchForMatch3(const int x, const int y, const vector<string> *map, const Point *origin) {
    vector<char> tb{};
    vector<char> lr{};
    for (int my = 0; my < 8; ++my) {
        if (my > 1 && my < 6) continue;
        tb.push_back(map[0][my + origin->y][x + origin->x]);
    }
    for (int mx = 0; mx < 8; ++mx) {
        if (mx > 1 && mx < 6) continue;
        lr.push_back(map[0][y + origin->y][mx + origin->x]);
    }

    for (char i: tb)
        if (ranges::find(lr, i) != lr.end()) return i;
    return '?';
}

char FindMissing(const int x, const int y, const vector<string> *map, const Point *origin) {
    vector<char> tb{};
    vector<char> lr{};
    for (int my = 0; my < 8; ++my) {
        tb.push_back(map[0][my + origin->y][x + origin->x]);
    }
    for (int mx = 0; mx < 8; ++mx) {
        lr.push_back(map[0][y + origin->y][mx + origin->x]);
    }

    vector<char> duplicatesTb{};
    vector<char> duplicatesLr{};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j == i) continue;
            if (tb[i] == tb[j]) {
                if (ranges::find(duplicatesTb, tb[i]) == duplicatesTb.end()) duplicatesTb.push_back(tb[i]);
            }
            if (lr[i] == lr[j]) {
                if (ranges::find(duplicatesLr, lr[i]) == duplicatesLr.end()) duplicatesLr.push_back(lr[i]);
            }
        }
    }

    for (int i = 0; i < 8; ++i) {
        if (ranges::find(duplicatesTb, tb[i]) == duplicatesTb.end() && tb[i] != '?') return tb[i];
        if (ranges::find(duplicatesLr, lr[i]) == duplicatesLr.end() && lr[i] != '?') return lr[i];
    }
    return '?';
}

int Count(const vector<char> *l, const char x) {
    int total{0};
    for (int i = 0; i < l->size(); ++i) {
        if (l[0][i] == x)total++;
    }
    return total;
}

void FillInQ(const int x, const int y, vector<string> *map, const Point *origin, const char missing) {
    vector<char> tb{};
    vector<char> lr{};
    for (int my = 0; my < 8; ++my) {
        tb.push_back(map[0][my + origin->y][x + origin->x]);
    }
    for (int mx = 0; mx < 8; ++mx) {
        lr.push_back(map[0][y + origin->y][mx + origin->x]);
    }

    if (Count(&tb, missing) < 2) {
        auto it = ranges::find(tb, '?');
        if (it != tb.end()) {
            auto index = distance(tb.begin(), it);
            map[0][index + origin->y][x + origin->x] = missing;
        }
    } else if (Count(&lr, missing) < 2) {
        auto it = ranges::find(lr, '?');
        if (it != lr.end()) {
            auto index = distance(lr.begin(), it);
            map[0][y + origin->y][index + origin->x] = missing;
        }
    }
}

int Day10::Part3() {
    auto map = Helpers::readFile(10, 3);
    vector<Point> origins{};
    int width = (map[0].length() - 2) / 6;
    int height = (map.size() - 2) / 6;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            origins.emplace_back(6 * x, 6 * y);
        }
    }

    int total{0};
    vector<string> words;
    for (auto origin: origins) {
        string word;
        for (int y = 2; y < 6; ++y) {
            for (int x = 2; x < 6; ++x) {
                char rune = SearchForMatch3(x, y, &map, &origin);
                map[y + origin.y][x + origin.x] = rune;
                word += rune;
            }
        }

        for (int i = 0; i < 16; ++i) {
            if (word[i] == '?') {
                int x = i % 4 + 2;
                int y = i / 4 + 2;

                char missing = FindMissing(x, y, &map, &origin);
                if (missing != '?') {
                    map[y + origin.y][x + origin.x] = missing;
                    FillInQ(x, y, &map, &origin, missing);
                    word[i] = missing;
                }
            }
        }

        words.push_back(word);

        total += CalculatePower(word);
    }

    return 0;
}
