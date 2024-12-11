#include <queue>
#include <set>

#include "CatFace.h"
#include "Day16.h"

void Day16::GenerateCombinations(vector<vector<CatFace> > *wheels, set<vector<int> > *faceCombos,
                                 const vector<int> &currentCombo,
                                 const int index) {
    for (int i = 0; i < (*wheels)[index].size(); ++i) {
        vector<int> nextCombo = currentCombo;
        nextCombo.push_back(i);
        if (index == wheels->size() - 1) faceCombos->insert(nextCombo);
        else GenerateCombinations(wheels, faceCombos, nextCombo, index + 1);
    }
}

int Day16::Part3() {
    const auto lines = Helpers::readFile(16, 3);

    vector<int> spinCounts{};
    for (const auto countStrings = Helpers::split(lines[0], ','); auto spin: countStrings) {
        spinCounts.push_back(stoi(spin));
    }

    set<char> symbols{};
    vector<vector<CatFace> > wheels{};
    for (int j = 0; j < spinCounts.size(); ++j) {
        vector<CatFace> wheel{};
        for (int i = 2; i < lines.size(); ++i) {
            if (j * 4 >= lines[i].length()) continue;
            auto row = lines[i].substr(4 * j, 3);
            if (row == "   ") continue;
            wheel.emplace_back(row);
            symbols.insert_range(wheel[wheel.size() - 1].chars2 | views::keys);
        }
        wheels.push_back(wheel);
    }

    const int wheelCount = spinCounts.size();

    vector<int> currentIndex{};
    currentIndex.resize(wheelCount);

    vector<CatFace *> currentFaces{};

    long long rounds = 256;
    long long total{0};

    set<vector<int> > faceCombos{};

    GenerateCombinations(&wheels, &faceCombos);

    vector<LinkedNode> nodes{};

    for (const auto &combo: faceCombos) {
        nodes.emplace_back(combo, &wheels);
    }

    for (auto &node: nodes) {
        currentIndex = node.positions;
        for (int j = 0; j < currentIndex.size(); ++j) {
            currentIndex[j] = (spinCounts[j] + currentIndex[j]) % wheels[j].size();
        }

        node.next = &*ranges::find_if(nodes, [currentIndex](const LinkedNode &p) { return p.equals(currentIndex); });
        auto up = node.upPosition(&wheels);
        auto down = node.downPosition(&wheels);
        node.up = &*ranges::find_if(nodes, [up](const LinkedNode &p) { return p.equals(up); });
        node.down = &*ranges::find_if(
            nodes, [down](const LinkedNode &p) { return p.equals(down); });
    }
    //dijkstra

    NodeScore start{&nodes[0]};

    map<LinkedNode *, int> dist{{start.node, 0}};
    map<LinkedNode *, LinkedNode *> prev{{start.node, nullptr}};

    for (auto &node: nodes) {
        NodeScore i{&node};
        if (&node == start.node) continue;
        dist.insert({&node, Helpers::Max});
        prev.insert({&node, nullptr});
    }

    priority_queue<NodeScore> q{};
    q.push(start);

    while (!q.empty()) {
        auto u = q.top();
        q.pop();

        //next
        NodeScore v{u.node->next};
        auto alt = dist[u.node] + v.distance;
        if (alt < dist[v.node]) {
            dist[v.node] = alt;
            prev[v.node] = u.node;
            q.push(v);
        }

        //up
        NodeScore vu{u.node->up->next};
        auto altU = dist[u.node] + vu.distance;
        if (altU < dist[vu.node]) {
            dist[vu.node] = altU;
            prev[vu.node] = u.node;
            q.push(vu);
        }

        //down
        NodeScore vd{u.node->down->next};
        auto altD = dist[u.node] + vd.distance;
        if (altD < dist[vd.node]) {
            dist[vd.node] = altD;
            prev[vd.node] = u.node;
            q.push(vd);
        }
    }

    return 0;
}
