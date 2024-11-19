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
    if (duplicatesTb.size() < 3 || duplicatesLr.size() < 3) return '?';

    for (int i = 0; i < 8; ++i) {
        if (ranges::find(duplicatesTb, tb[i]) == duplicatesTb.end() && tb[i] != '?') return tb[i];
        if (ranges::find(duplicatesLr, lr[i]) == duplicatesLr.end() && lr[i] != '?') return lr[i];
    }
    return '?';
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

    if (Day10::Count(&tb, missing) < 2) {
        auto it = ranges::find(tb, '?');
        if (it != tb.end()) {
            auto index = distance(tb.begin(), it);
            map[0][index + origin->y][x + origin->x] = missing;
        }
    } else if (Day10::Count(&lr, missing) < 2) {
        auto it = ranges::find(lr, '?');
        if (it != lr.end()) {
            auto index = distance(lr.begin(), it);
            map[0][y + origin->y][index + origin->x] = missing;
        }
    }
}

void PrintMap(const vector<string> &map) {
    string text;
    for (const auto &line: map) text += line + "\n";

    cout << endl << text << endl;
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

    // PrintMap(map);

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
        // PrintMap(map);
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
                // PrintMap(map);
            }
        }

        words.push_back(word);

        if (ValidWord(&word))
            total += CalculatePower(word);
    }

    vector<Point> mapsToSolve{};
    for (int i = 0; i < words.size(); ++i) {
        if (!ValidWord(&words[i])) mapsToSolve.push_back(origins[i]);
    }
    int mapsSolved;

    do {
        mapsSolved = 0;
        vector<Point *> originsSolved{};
        for (auto origin: mapsToSolve) {
            string word;
            for (int y = 2; y < 6; ++y) {
                for (int x = 2; x < 6; ++x) {
                    char rune = SearchForMatch3(x, y, &map, &origin);
                    map[y + origin.y][x + origin.x] = rune;
                    word += rune;
                }
            }
            // PrintMap(map);
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
                    // PrintMap(map);
                }
            }

            if (ValidWord(&word)) {
                total += CalculatePower(word);
                originsSolved.push_back(&origin);
                mapsSolved++;
            }
        }
        for (auto origin: originsSolved) {
            auto it = find_if(mapsToSolve.begin(), mapsToSolve.end(), [origin](Point &o) {
                return o.x == origin->x && o.y == origin->y;
            });
            mapsToSolve.erase(it);
        }
    } while (mapsSolved > 0);


    return total;
}
