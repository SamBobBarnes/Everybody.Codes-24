#include <queue>
#include <set>

#include "Day15.h"

bool IsHerb(char p) {
    switch (p) {
        case '.':
        case '#':
        case '~':
            return false;
        default: return true;
    }
}

void EraseParentageAndHerb(vector<vector<GardenPoint> > *garden, const char herb) {
    for (int y = 0; y < garden->size(); ++y) {
        for (int x = 0; x < (*garden)[y].size(); ++x) {
            (*garden)[y][x].parent = nullptr;
            if ((*garden)[y][x].tileChar == herb) (*garden)[y][x].herb = false;
        }
    }
}

GardenPoint *Day15::bfs(vector<vector<GardenPoint> > *garden, GardenPoint *start, GardenPoint *goal) {
    vector<GardenPoint *> visited{};
    queue<GardenPoint *> q;
    const bool lookForHerb = goal == nullptr;

    q.push(start);

    while (!q.empty()) {
        const auto v = q.front();
        if (lookForHerb && v->herb) {
            break;
        }
        if (!lookForHerb && v->x == goal->x && v->y == goal->y) {
            break;
        }
        q.pop();
        auto edges = GetEdges(garden, v);
        for (auto w: edges) {
            if (ranges::find(visited, w) != visited.end()) continue;
            visited.push_back(w);
            w->parent = v;
            q.push(w);
        }
    }

    return q.front();
}

int Day15::Part2() {
    const auto lines = Helpers::readFile(15, 2);
    vector<vector<GardenPoint> > garden{};
    set<char> herbs{};
    for (int y = 0; y < lines.size(); ++y) {
        vector<GardenPoint> row{};
        for (int x = 0; x < lines[0].length(); ++x) {
            bool isHerb = IsHerb(lines[y][x]);
            GardenPoint p{x, y, lines[y][x] == '#' || lines[y][x] == '~', isHerb, lines[y][x]};
            row.push_back(p);
            if (isHerb) herbs.insert(lines[y][x]);
        }
        garden.push_back(row);
    }

    GardenPoint *start = nullptr;
    GardenPoint *entrance = nullptr;

    for (int i = 0; i < garden[0].size(); ++i) {
        if (!garden[0][i].impasse) {
            start = &garden[0][i];
            entrance = &garden[0][i];
            break;
        }
    }
    int total{0};

    while (!herbs.empty()) {
        const auto goal = bfs(&garden, start);
        const auto it = ranges::find(herbs, goal->tileChar);
        herbs.erase(it);

        const GardenPoint *current = goal;
        while (current != start) {
            total++;
            current = current->parent;
        }

        start = goal;
        EraseParentageAndHerb(&garden, goal->tileChar);
    }

    const auto goal = bfs(&garden, start, entrance);

    const GardenPoint *current = goal;
    while (current != start) {
        total++;
        current = current->parent;
    }

    return total;
}
