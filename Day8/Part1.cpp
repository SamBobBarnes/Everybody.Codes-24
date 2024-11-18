#include "Day8.h"


int WidthOfTower(int height) {
    return 1 + 2 * (height - 1);
}

int TotalBlocks(int height) {
    int total{0};
    for (int i = 1; i <= height; i++) {
        total += WidthOfTower(i);
    }
    return total;
}

int Day8::Part1() {
    int blocksAvailable = stoi(Helpers::readFile(8, 1)[0]);
    int index{0};
    int currentUsage{0};
    while (currentUsage <= blocksAvailable) {
        index++;
        currentUsage = TotalBlocks(index);
    }

    int width = WidthOfTower(index);
    int blocksNeeded = currentUsage - blocksAvailable;

    return width * blocksNeeded;
}
