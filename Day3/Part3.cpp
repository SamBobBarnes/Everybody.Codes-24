//
// Created by sb17057 on 11/13/2024.
//

#include "Day3.h"
#include "../Point.h"

int Day3::Part3() {
    cout << endl;
    auto lines = Helpers::readFile("Day3/Part3.txt");
    int height = lines.size();
    int width = lines[0].length();

    vector<vector<int> > map{};

    for (int y = -1; y <= height; y++) {
        vector<int> row{};
        for (int x = -1; x <= width; x++) {
            if (x < 0 || y < 0 || y == height || x == width) row.push_back(0);
            else {
                int hole = lines[y][x] == '#' ? 1 : 0;
                row.push_back(hole);
            }
        }
        map.push_back(row);
    }

    height += 2;
    width += 2;

    int currentDepth{0};
    vector<Point> holesToDig{};
    do {
        for (const auto &point: holesToDig) {
            map[point.y][point.x] = currentDepth + 1;
        }
        currentDepth++;
        holesToDig.clear();

        // PrintMap(&map);
        cout << endl;

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (y == 0 || y == height - 1 || x == 0 || x == width - 1) continue;
                if (map[y][x] == currentDepth &&
                    map[y][x + 1] == currentDepth &&
                    map[y][x - 1] == currentDepth &&
                    map[y + 1][x] == currentDepth &&
                    map[y - 1][x] == currentDepth &&
                    map[y - 1][x - 1] == currentDepth &&
                    map[y - 1][x + 1] == currentDepth &&
                    map[y + 1][x + 1] == currentDepth &&
                    map[y + 1][x - 1] == currentDepth)
                    holesToDig.emplace_back(x, y);
            }
        }
    } while (!holesToDig.empty());

    int total{0};
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            total += map[y][x];
        }
    }
    return total;
}
