#include "Day13.h"
#include "Platform.h"

int Day13::Part1() {
    auto lines = Helpers::readFile(13, 1);
    vector<Platform> platforms{};

    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[y].length(); ++x) {
            if (lines[y][x] == '#') continue;
            if (lines[y][x] == 'S' || lines[y][x] == 'E') platforms.emplace_back(x, y, 0);
            else platforms.emplace_back(x, y, lines[y][x] - '0');
        }
    }

    for (int i = 0; i < platforms.size(); ++i) {
        for (int j = 0; j < platforms.size(); ++j) {
            if (i == j)continue;

            if (platforms[j].position.x == platforms[i].position.x && platforms[j].position.y == platforms[i].position.y
                - 1)
                platforms[i].up = &platforms[j];
            if (platforms[j].position.x == platforms[i].position.x && platforms[j].position.y == platforms[i].position.y
                + 1)
                platforms[i].down = &platforms[j];
            if (platforms[j].position.x == platforms[i].position.x - 1 && platforms[j].position.y == platforms[i].
                position.y)
                platforms[i].left = &platforms[j];
            if (platforms[j].position.x == platforms[i].position.x + 1 && platforms[j].position.y == platforms[i].
                position.y)
                platforms[i].right = &platforms[j];
        }
    }

    return 0;
}
