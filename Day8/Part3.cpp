#include "Day8.h"

int HeightOfTallLayer(const int prevLayerThickness, const int priests, const int acolytes) {
    return ((prevLayerThickness * priests) % acolytes) + acolytes;
}

long long RemoveBlocksFromColumn(const long long priests, const long long acolytes, const long long baseWidth,
                                 const long long columnHeight) {
    return (priests * baseWidth * columnHeight) % acolytes;
}

int Day8::Part3() {
    int highPriests = stoi(Helpers::readFile(8, 3)[0]);
    int highPriestAcolytes{10};
    int material{202400000};

    int index{1};
    int currentUsage{1};
    int currentShell{1};
    int prevLayerThickness{1};
    vector towerColumns{1};

    while (currentShell <= material) {
        index++;

        int layerHeight = HeightOfTallLayer(prevLayerThickness, highPriests, highPriestAcolytes);
        prevLayerThickness = layerHeight;
        int layerWidth = WidthOfTower(index);
        currentUsage += layerHeight * layerWidth;

        for (int &column: towerColumns) {
            column += layerHeight;
        }

        towerColumns.push_back(layerHeight);

        int tempUsage = currentUsage;
        int firstLayer = RemoveBlocksFromColumn(highPriests, highPriestAcolytes, layerWidth, towerColumns[0]);
        tempUsage -= firstLayer;
        for (int i = 1; i < towerColumns.size() - 1; i++) {
            tempUsage -= 2 * (RemoveBlocksFromColumn(highPriests, highPriestAcolytes, layerWidth, towerColumns[i]));
        }
        currentShell = tempUsage;
    }

    int blocksNeeded = currentShell - material;

    return blocksNeeded;
}
