#ifndef DAY15_H
#define DAY15_H

#include <set>

#include "../Helpers.h"
#include "../Point.h"
#include "GardenPoint.h"

using namespace std;

class Day15 {
public:
    static int Part1();

    static int Part2();

    static int Part3();

    static vector<GardenPoint *> GetEdges(vector<vector<GardenPoint> > *garden, const GardenPoint *current) {
        vector<GardenPoint *> edges{};
        if (current->y > 0 && !(*garden)[current->y - 1][current->x].impasse)
            edges.push_back(
                &(*garden)[current->y - 1][current->x]);
        if (current->y < garden->size() - 1 && !(*garden)[current->y + 1][current->x].impasse)
            edges.push_back(
                &(*garden)[current->y + 1][current->x]);
        if (current->x > 0 && !(*garden)[current->y][current->x - 1].impasse)
            edges.push_back(
                &(*garden)[current->y][current->x - 1]);
        if (current->x < (*garden)[0].size() - 1 && !(*garden)[current->y][current->x + 1].impasse)
            edges.push_back(
                &(*garden)[current->y][current->x + 1]);
        return edges;
    }

    static GardenPoint *bfs(vector<vector<GardenPoint> > *garden, GardenPoint *star, GardenPoint *goal = nullptr);
};

#endif //DAY15_H
