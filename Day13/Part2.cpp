#include <map>
#include <queue>

#include "Day13.h"
#include "Platform.h"

int Day13::Part2() {
    auto lines = Helpers::readFile(13, 2);
    vector<Platform> platforms{};
    Point startPos{-1, -1};
    Point endPos{-1, -1};

    Platform *start = nullptr;
    Platform *end = nullptr;

    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[y].length(); ++x) {
            if (lines[y][x] == '#' || lines[y][x] == ' ') continue;
            if (lines[y][x] == 'S') {
                platforms.emplace_back(x, y, 0);
                startPos = {x, y};
            } else if (lines[y][x] == 'E') {
                platforms.emplace_back(x, y, 0);
                endPos = {x, y};
            } else platforms.emplace_back(x, y, lines[y][x] - '0');
        }
    }

    start = &*ranges::find_if(platforms, [startPos](const Platform &p) {
        return startPos == p.position;
    });
    end = &*ranges::find_if(platforms, [endPos](const Platform &p) {
        return endPos == p.position;
    });

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

    if (start == nullptr) {
        cerr << "TILT start!" << endl;
        return -1;
    }

    priority_queue<PlatformDistance, std::vector<PlatformDistance>, greater<PlatformDistance> > q{};
    map<Platform *, int> dist{};
    map<Platform *, Platform *> prev{};
    vector<Platform *> visited{};

    q.emplace(start, 0);

    for (auto &platform: platforms) {
        if (platform == *start) {
            prev[&platform] = nullptr;
            continue;
        }
        prev[&platform] = nullptr;
        dist[&platform] = Max;
        q.emplace(&platform, Max);
    }


    while (!q.empty()) {
        auto pd = q.top();
        q.pop();
        if (ranges::find(visited, pd.pointer) != visited.end()) continue;
        visited.push_back(pd.pointer);
        if (pd.pointer == end) break;

        for (auto neighbor: pd.pointer->GetNeighbors()) {
            auto np = get<0>(neighbor);
            int alt = dist[pd.pointer] + get<1>(neighbor);
            if (alt < dist[np]) {
                dist[np] = alt;
                prev[np] = pd.pointer;
                q.emplace(np, alt);
            }
        }
    }

    return dist[end];
}
