#include <queue>

#include "Day15.h"

vector<GardenPoint *> GetEdges(vector<vector<GardenPoint> > *garden, const GardenPoint *current) {
    vector<GardenPoint *> edges{};
    if (current->y > 0 && !(*garden)[current->y - 1][current->x].bush)
        edges.push_back(
            &(*garden)[current->y - 1][current->x]);
    if (current->y < garden->size() - 1 && !(*garden)[current->y + 1][current->x].bush)
        edges.push_back(
            &(*garden)[current->y + 1][current->x]);
    if (current->x > 0 && !(*garden)[current->y][current->x - 1].bush)
        edges.push_back(
            &(*garden)[current->y][current->x - 1]);
    if (current->x < (*garden)[0].size() - 1 && !(*garden)[current->y][current->x + 1].bush)
        edges.push_back(
            &(*garden)[current->y][current->x + 1]);
    return edges;
}

int Day15::Part1() {
    auto lines = Helpers::readFile(15, 1);
    vector<vector<char> > gardenChars{};
    vector<vector<GardenPoint> > garden{};

    for (int i = 0; i < lines.size(); ++i) {
        gardenChars.push_back(Helpers::splitIntoChars(lines[i]));
    }

    for (int y = 0; y < gardenChars.size(); ++y) {
        vector<GardenPoint> row{};
        for (int x = 0; x < gardenChars[0].size(); ++x) {
            GardenPoint p{x, y, gardenChars[y][x] == '#', gardenChars[y][x] == 'H'};
            row.push_back(p);
        }
        garden.push_back(row);
    }


    vector<GardenPoint *> visited{};
    queue<GardenPoint *> q;
    GardenPoint *start = nullptr;

    for (int i = 0; i < garden[0].size(); ++i) {
        if (!garden[0][i].bush) {
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
