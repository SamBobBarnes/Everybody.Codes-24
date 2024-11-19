#include <map>

#include "Day10.h"

int CalculatePower(string word) {
    map<char, int> powers{
        {'A', 1}, {'B', 2}, {'C', 3}, {'D', 4}, {'E', 5}, {'F', 6}, {'G', 7}, {'H', 8}, {'I', 9}, {'J', 10},
        {'K', 11}, {'L', 12}, {'M', 13}, {'N', 14}, {'O', 15}, {'P', 16}, {'Q', 17}, {'R', 18}, {'S', 19}, {'T', 20},
        {'U', 21}, {'V', 22}, {'W', 23}, {'X', 24}, {'Y', 25}, {'Z', 26}
    };

    int total{0};
    for (int i = 0; i < word.length(); ++i) {
        total += powers[word[i]] * (i + 1);
    }
    return total;
}

int Day10::Part2() {
    auto lines = Helpers::readFile(10, 2);
    vector<vector<vector<char> > > maps{};
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 15; i++) {
            vector<vector<char> > map{};
            for (int y = 0; y < 8; y++) {
                vector<char> row{};
                for (int x = 0; x < 8; x++) {
                    row.push_back(lines[y + 9 * j][x + 9 * i]);
                }
                map.push_back(row);
            }
            maps.push_back(map);
        }
    }

    int total{0};
    for (auto map: maps) {
        string word;
        for (int y = 2; y < 6; ++y) {
            for (int x = 2; x < 6; ++x) {
                word += SearchForMatch(x, y, &map);
            }
        }

        total += CalculatePower(word);
    }

    return total;
}
