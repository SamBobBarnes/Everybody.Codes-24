//
// Created by Samuel Barnes on 11/11/24.
//

#include "Day2.h"

int Day2::Part3() {
    int total = 0;
    const std::string filePath{"Day2/Part3.txt"};
    std::vector<std::string> words{
        "VUU", "QGW", "NG", "VNPCCPZCEJ", "MX", "XH", "BTYD", "SHLX", "XI", "ABTW", "EQJNTYVVXM", "LOL", "MCT", "HV",
        "BUURUPZFKP", "K", "KUT", "LX", "KGDT", "G", "JDQL", "R", "NV", "HUCP", "XOGC", "DT", "XSO", "ZMEJ", "B",
        "MPWFMMMKAI", "URP", "JGZECVSPMW", "EYED", "OO", "HK", "ATOOEYDSOQ", "H", "LATL", "ASUC", "QJQAEVGUDR", "QN",
        "WZ", "RYI", "SGB", "FU", "RHMW", "LO", "MSIQIBYDGZ", "KG", "SQWUMWZKHH", "BAM", "YJNQ", "CCS", "YZDHFEVEEL",
        "RA", "PN", "S", "EA", "AYSEMKGCIT", "CZ", "ZJOESISAVM", "MHA", "OTP", "XMMT", "J", "Y", "RPAJIPUVJE", "JZMA",
        "WRWNHSHZQS", "NU", "ZRZKAHGBBL", "LZOVFCFTLL", "RGW", "PWTWRRKDRD", "AHNM", "NLB", "DCXENOOMNU", "MIZN",
        "WYIG", "X", "YK", "LTVBWTGLNF", "QVP", "EQO", "JBN", "AHP", "Q", "GGV", "CEVYJRNGQR", "DYER", "EKQ", "QQ",
        "UTJO"
    };

    std::vector<std::string> lines = Helpers::readFile(filePath);
    const int width = 200;
    const int height = 107;


    char grid[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            grid[i][j] = lines[i][j];
        }
    }

    std::vector<std::vector<bool> > map = createMap(width, height);

    for (const std::string &word: words) {
        auto result = findWordOnGrid(width, height, reinterpret_cast<char *>(grid), word);
        if (result.found) {
            auto tempMap = pointsToIntMap(result.symbolLocations, width, height);
            map = orMap(map, tempMap, width, height);
        }
    }

    printMap(&map, reinterpret_cast<char *>(grid));

    total = countPoints(map, width, height);
    return total;
}
