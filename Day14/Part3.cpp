#include <map>
#include <queue>
#include <set>

#include "Day14.h"

vector<Point3> getNeighbors(Point3 p, const map<Point3, bool> *points) {
    vector<Point3> list{};
    if (points->contains({p.x, p.y, p.z + 1})) list.push_back({p.x, p.y, p.z + 1});
    if (points->contains({p.x, p.y, p.z - 1})) list.push_back({p.x, p.y, p.z - 1});
    if (points->contains({p.x, p.y + 1, p.z})) list.push_back({p.x, p.y + 1, p.z});
    if (points->contains({p.x, p.y - 1, p.z})) list.push_back({p.x, p.y - 1, p.z});
    if (points->contains({p.x + 1, p.y, p.z})) list.push_back({p.x + 1, p.y, p.z});
    if (points->contains({p.x - 1, p.y, p.z})) list.push_back({p.x - 1, p.y, p.z});
    return list;
};

int Day14::Part3() {
    auto lines = Helpers::readFile(14, 3);

    map<Point3, bool> points{};
    map<Point3, bool> leaves{};


    for (auto line: lines) {
        Point3 current{0, 0, 0};
        auto directions = Helpers::split(line, ',');
        for (auto direction: directions) {
            GrowthPlan plan{direction};
            switch (plan.direction) {
                case Up:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.y++;
                        points[current] = true;
                    }
                    break;
                case Down:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.y--;
                        points[current] = true;
                    }
                    break;
                case Left:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.x--;
                        points[current] = true;
                    }
                    break;
                case Right:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.x++;
                        points[current] = true;
                    }
                    break;
                case Forward:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.z++;
                        points[current] = true;
                    }
                    break;
                case Backward:
                    for (int i = 0; i < plan.distance; ++i) {
                        current.z--;
                        points[current] = true;
                    }
                    break;
            }
        }
        leaves[current] = true;
    }

    vector<Point3> trunk{};

    for (const auto key: points | views::keys) {
        if (key.z == 0 && key.x == 0) trunk.push_back(key);
    }

    vector<int> totals{};

    auto cmp = [](const tuple<Point3, int> l, const tuple<Point3, int> r) { return get<1>(l) > get<1>(r); };

    for (auto end: trunk) {
        // auto end = trunk[5];
        int minTotal{0};
        for (const auto leaf: leaves | views::keys) {
            priority_queue<tuple<Point3, int>, std::vector<tuple<Point3, int> >, decltype(cmp)> q{};
            map<Point3, int> dist{};
            map<Point3, Point3> prev{};
            vector<Point3> visited{};
            dist[leaf] = 0;
            q.push({leaf, 0});

            for (auto point: points | views::keys) {
                if (point == leaf) {
                    prev[leaf] = {};
                    continue;
                }
                prev[point] = {};
                dist[point] = Max;
                q.push({point, Max});
            }

            while (!q.empty()) {
                auto u = q.top();
                q.pop();
                auto p = get<0>(u);
                if (ranges::find(visited, p) != visited.end()) continue;
                visited.push_back(p);
                if (p == end) break;

                auto neighbors = getNeighbors(p, &points);
                for (auto neighbor: neighbors) {
                    int alt = dist[p] + 1;
                    if (alt < dist[neighbor]) {
                        prev[neighbor] = p;
                        dist[neighbor] = alt;
                        q.push({neighbor, alt});
                    }
                }
            }
            minTotal += dist[end];
        }
        totals.push_back(minTotal);
    }


    return ranges::min(totals);
}
