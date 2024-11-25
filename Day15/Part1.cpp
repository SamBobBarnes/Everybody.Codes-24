#include <queue>

#include "Day15.h"

int Day15::Part1() {
    const auto lines = Helpers::readFile(15, 1);
    vector<vector<GardenPoint> > garden{};

    for (int y = 0; y < lines.size(); ++y) {
        vector<GardenPoint> row{};
        for (int x = 0; x < lines[0].length(); ++x) {
            GardenPoint p{x, y, lines[y][x] == '#', lines[y][x] == 'H', lines[y][x]};
            row.push_back(p);
        }
        garden.push_back(row);
    }


    vector<GardenPoint *> visited{};
    queue<GardenPoint *> q;
    GardenPoint *start = nullptr;

    for (int i = 0; i < garden[0].size(); ++i) {
        if (!garden[0][i].impasse) {
            start = &garden[0][i];
            break;
        }
    }

    q.push(start);

    while (!q.empty()) {
        const auto v = q.front();
        if (v->herb) {
            break;
        }
        q.pop();
        auto edges = GetEdges(&garden, v);
        for (auto w: edges) {
            if (ranges::find(visited, w) != visited.end()) continue;
            visited.push_back(w);
            w->parent = v;
            q.push(w);
        }
    }

    int total{0};

    const GardenPoint *current = q.front();
    while (current != start) {
        total++;
        current = current->parent;
    }

    return total * 2;
}
