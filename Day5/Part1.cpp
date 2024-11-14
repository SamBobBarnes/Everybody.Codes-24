//
// Created by sb17057 on 11/14/2024.
//

#include "../Point.h"
#include "Day5.h"

int Day5::Part1() {
    // cout << endl;
    auto lines = Helpers::readFile(5, 1);
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

    int rounds{10};
    int currentCol{0};
    int maxHeight = knights[0].size();
    int finalNumber{0};
    // printDance(&knights, maxHeight);

    for (int i = 0; i < rounds; i++) {
        int nextCol = currentCol + 1 == knights.size() ? 0 : currentCol + 1;

        Point clapperPos{currentCol, 0};
        int clapperValue = knights[clapperPos.x][clapperPos.y];
        int nextColLength = knights[nextCol].size();
        int landIndex = -1;
        bool rightSide = false;

        for (int c = 0; c < clapperValue; c++) {
            if (!rightSide) {
                //going down
                landIndex++;
                if (landIndex == nextColLength) {
                    landIndex--;
                    rightSide = true;
                }
            } else {
                //going up
                landIndex--;
                if (landIndex < 0) {
                    landIndex++;
                    rightSide = false;
                }
            }
        }
        Point finalPlacement = {nextCol, landIndex + (rightSide ? 1 : 0)};


        // cout << endl << "Knight " << clapperValue << " moves from {" << clapperPos.x << "," << clapperPos.y << "} to {"
        //         <<
        //         finalPlacement.x << "," << finalPlacement.y << "}. And all the knights cry """;


        if (finalPlacement.y == nextColLength) knights[nextCol].push_back(clapperValue);
        else knights[nextCol].insert(knights[nextCol].begin() + finalPlacement.y, clapperValue);
        knights[currentCol].erase(knights[currentCol].begin());

        string cry = "";

        for (const auto &col: knights) {
            if (col.size() > maxHeight) maxHeight = col.size();
            cry += to_string(col[0]);
        }

        // cout << cry << "!""" << endl;
        finalNumber = std::stoi(cry);
        // printDance(&knights, maxHeight);

        currentCol = nextCol;
    }

    return finalNumber;
}
