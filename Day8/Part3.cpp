#include "Day8.h"

int HeightOfTallLayer(const int prevLayerThickness, const int priests, const int acolytes) {
    return ((prevLayerThickness * priests) % acolytes) + acolytes;
}

int RemoveBlocksFromColumn(const int priests, const int acolytes, const int baseWidth, const int columnHeight) {
    return (priests * baseWidth * columnHeight) % acolytes;
}

int Day8::Part3() {
    int highPriests = stoi(Helpers::readFile(8, 3)[0]);
    int highPriestAcolytes{10};
    int material{202400000};

    // int highPriests{2};
    // int highPriestAcolytes{5};
    // int material{160};

    int index{1};
    int currentUsage{1};
    int currentShell{1};
    int prevLayerThickness{1};
    vector<int> towerColumns{1};

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
        tempUsage -= RemoveBlocksFromColumn(highPriests, highPriestAcolytes, layerWidth, towerColumns[0]);

        for (int i = 1; i < towerColumns.size() - 1; i++) {
            tempUsage -= 2 * (RemoveBlocksFromColumn(highPriests, highPriestAcolytes, layerWidth, towerColumns[i]));
        }
        currentShell = tempUsage;
    }

    int blocksNeeded = currentShell - material;

    return blocksNeeded;
}
