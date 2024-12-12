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

int Day16::GetLimit(const LinkedNode *current, const bool max, const int depth, const int maxDepth) {
    if (depth == maxDepth) return current->value;

    int scores[3]{};

    scores[0] = GetLimit(current->next, max, depth + 1, maxDepth);
    scores[1] = GetLimit(current->up->next, max, depth + 1, maxDepth);
    scores[2] = GetLimit(current->down->next, max, depth + 1, maxDepth);

    int largest{-1};
    int smallest{Helpers::Max};

    for (auto score: scores) {
        if (score > largest) largest = score;
        if (score < smallest) smallest = score;
    }

    if (depth == 0) return max ? largest : smallest;
    return current->value + (max ? largest : smallest);
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

    LinkedNode *start = &nodes[0];

    int maxDepth = 2;

    int max = GetLimit(start, true, 0, maxDepth);
    int min = GetLimit(start, false, 0, maxDepth);


    return 0;
}
