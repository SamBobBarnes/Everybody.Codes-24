//
// Created by sb17057 on 11/14/2024.
//

#include <algorithm>

#include "Day5.h"
#include "../Point.h"
#include "Bucket.h"

int Day5::Part2() {
    cout << endl;
    auto lines = Helpers::readFile(5, 2);
    vector<vector<int> > tempKnights{};
    vector<vector<int> > knights{};
    for (auto &line: lines) {
        vector<int> row{};
        auto chars = Helpers::split(line);
        for (auto &dancer: chars) {
            row.push_back(std::stoi(dancer));
        }
        tempKnights.push_back(row);
    }
    for (int x = 0; x < tempKnights[0].size(); x++) {
        vector<int> row{};
        for (auto &tempKnight: tempKnights) {
            row.push_back(tempKnight[x]);
        }
        knights.push_back(row);
    }

    int rounds{1000000000};
    int currentCol{0};
    int maxHeight = knights[0].size();
    int finalNumber{0};
    Bucket cries{};
    printDance(&knights, maxHeight);

    for (int i = 0; i < rounds; i++) {
        int nextCol = currentCol + 1 == knights.size() ? 0 : currentCol + 1;

        Point clapperPos{currentCol, 0};
        int clapperValue = knights[clapperPos.x][clapperPos.y];
        int nextColLength = knights[nextCol].size();
        bool rightSide = clapperValue / (nextColLength + 1) % 2;
        int landIndex = ((clapperValue % nextColLength) - 1) + (rightSide ? nextColLength - 1 : 0);
        if (landIndex < 0) landIndex = nextColLength - 1;

        Point finalPlacement = {nextCol, landIndex + (rightSide ? 1 : 0)};


        cout << endl << "Knight " << clapperValue << " moves from {" << clapperPos.x << "," << clapperPos.y << "} to {"
                << finalPlacement.x << "," << finalPlacement.y << "}. And all the knights cry """;


        if (finalPlacement.y == nextColLength) knights[nextCol].push_back(clapperValue);
        else knights[nextCol].insert(knights[nextCol].begin() + finalPlacement.y, clapperValue);
        knights[currentCol].erase(knights[currentCol].begin());

        int cry{0};
        int index = knights.size() - 1;
        for (const auto &col: knights) {
            if (col.size() > maxHeight) maxHeight = col.size();
            int power = pow(10, index);
            cry += col[0] * power;
            index--;
        }

        cout << cry << "!""" << endl;
        printDance(&knights, maxHeight);

        // if (cries.Collect(cry, i)) {
        //     cout << "first duplicate found at line " << i << endl;
        //     break;
        // }

        // cries.push_back(finalNumber);

        currentCol = nextCol;
    }

    cries.PrintData();

    return finalNumber;
}
