//
// Created by sb17057 on 11/13/2024.
//

#include "Day4.h"
#include <string>

int Day4::Part3() {
    auto lines = Helpers::readFile("Day4/Part3.txt");
    vector<int> nails{};

    int runningTotal{0};
    int max{0};
    int min{0};

    for (const auto &line: lines) {
        int nail = std::stoi(line) - 27000000;
        if (max == 0 || nail > max) max = nail;
        if (min == 0 || nail < min) min = nail;
        runningTotal += nail;
        nails.push_back(nail);
    }
    vector<tuple<int, int, int, int> > totals{};
    int goal = runningTotal / lines.size() + 1;
    int ups{0};
    int downs{0};

    int total{0};
    for (int nail: nails) {
        if (nail < goal) {
            total += goal - nail;
            ups += goal - nail;
        } else {
            total += nail - goal;
            downs += nail - goal;
        }
    }

    totals.emplace_back(goal, ups, downs, total);

    cout << endl;
    cout << leftpad("Average", 10) << " |" << leftpad("Ups", 10) << " |" << leftpad("Downs", 10) << " |" <<
            leftpad("Total", 10) << endl;
    for (auto &line: totals) {
        cout << leftpad(to_string(get<0>(line)), 10) << " |" << leftpad(to_string(get<1>(line)), 10) << " |" <<
                leftpad(to_string(get<2>(line)), 10) << " |" << leftpad(to_string(get<3>(line)), 10) << endl;
    }

    return total;
}
