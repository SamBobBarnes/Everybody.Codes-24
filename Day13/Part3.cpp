#include <map>
#include <queue>

#include "Day13.h"
#include "Platform.h"

int Day13::Part3() {
    auto lines = Helpers::readFile(13, 3);
    int height = lines.size();
    int width = lines[0].length();
    vector<Platform> platforms{};
    vector<Point> startPos{};
    Point endPos{-1, -1};

    vector<Platform *> startList{};
    Platform *end = nullptr;

    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[y].length(); ++x) {
            if (lines[y][x] == '#' || lines[y][x] == ' ') continue;
            if (lines[y][x] == 'S') {
                platforms.emplace_back(x, y, 0);
                startPos.emplace_back(x, y);
            } else if (lines[y][x] == 'E') {
                platforms.emplace_back(x, y, 0);
                endPos = {x, y};
            } else platforms.emplace_back(x, y, lines[y][x] - '0');
        }
    }

    for (auto startP: startPos)
        startList.push_back(&*ranges::find_if(platforms, [startP](const Platform &p) {
            return startP == p.position;
        }));
    end = &*ranges::find_if(platforms, [endPos](const Platform &p) {
        return endPos == p.position;
    });

    for (int i = 0; i < platforms.size(); ++i) {
        for (int j = 0; j < platforms.size(); ++j) {
            if (i == j)continue;
            if (platforms[j].position.x == 0 || platforms[j].position.x == width - 1 || platforms[j].position.y == 0 ||
                platforms[j].position.y == height - 1)
                continue;

            if (platforms[j].position.x == platforms[i].position.x && platforms[j].position.y == platforms[i].
                position.y
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
    int shortest{Max};

    for (auto start: startList) {
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
        bool tooLong{false};

        while (!q.empty()) {
            auto pd = q.top();
            q.pop();
            if (pd.distance >= shortest) {
                tooLong = true;
                break;
            }
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
        if (!tooLong)
            shortest = dist[end];
    }

    return shortest;
}
