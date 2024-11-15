//
// Created by sb17057 on 11/14/2024.
//

#include <algorithm>

#include "Day5.h"
#include "../Point.h"
#include "Bucket.h"

long long Day5::Part2() {
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
    int intWidth = knights[0][0] > 10 ? 2 : 1;
    long long finalNumber{0};
    int checkAmount = 2024;
    Bucket cries{checkAmount};
    // printDance(&knights, maxHeight);

    for (int i = 0; i < rounds; i++) {
        int nextCol = currentCol + 1 == knights.size() ? 0 : currentCol + 1;

        Point clapperPos{currentCol, 0};
        int clapperValue = knights[clapperPos.x][clapperPos.y];
        int nextColLength = knights[nextCol].size();
        bool rightSide = nextColLength > 1 ? clapperValue / nextColLength % 2 : !(clapperValue % 2);
        int landIndex = ((clapperValue % nextColLength) - 1) + (rightSide ? nextColLength - 1 : 0);
        if (landIndex < 0) landIndex = nextColLength - 1;

        Point finalPlacement = {nextCol, landIndex + (rightSide ? 1 : 0)};


        // cout << endl << "Knight " << clapperValue << " moves from {" << clapperPos.x << "," << clapperPos.y << "} to {"
        //         << finalPlacement.x << "," << finalPlacement.y << "}. And all the knights cry """;


        if (finalPlacement.y == nextColLength) knights[nextCol].push_back(clapperValue);
        else knights[nextCol].insert(knights[nextCol].begin() + finalPlacement.y, clapperValue);
        knights[currentCol].erase(knights[currentCol].begin());

        int cry{0};
        int index = knights.size() - 1;
        for (const auto &col: knights) {
            if (col.size() > maxHeight) maxHeight = col.size();
            int base{10};
            if (intWidth > 1) base = 100;
            int power = pow(base, index);
            cry += col[0] * power;
            index--;
        }

        // cout << cry << "!""" << endl;
        // printDance(&knights, maxHeight);

        if (cries.Collect(cry, i)) {
            // cout << checkAmount << " iteration of " << cry << " found on iteration " << i << endl;
            finalNumber = (long long) cry * (long long) (i + 1);
            break;
        }

        currentCol = nextCol;
    }

    // cries.PrintData();

    return finalNumber;
}
