#include "Day8.h"

int HeightOfLayer(int prevLayerThickness, int priests, int acolytes) {
    return (prevLayerThickness * priests) % acolytes;
}

int Day8::Part2() {
    int priests = stoi(Helpers::readFile(8, 2)[0]);
    int acolytes{1111};
    int material{20240000};

    int index{1};
    int currentUsage{1};
    int prevLayerThickness{1};

    while (currentUsage <= material) {
        index++;
        int layerHeight = HeightOfLayer(prevLayerThickness, priests, acolytes);
        prevLayerThickness = layerHeight;
        int layerWidth = WidthOfTower(index);
        currentUsage += layerHeight * layerWidth;
    }

    int blocksNeeded = currentUsage - material;
    int width = WidthOfTower(index);

    return width * blocksNeeded;
}
