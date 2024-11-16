//
// Created by Samuel Barnes on 11/16/24.
//

#include <algorithm>
#include <__ranges/iota_view.h>

#include "Day7.h"
#include "Plan.h"

string leftPad(const int number, const int width) {
    string text = to_string(number);
    if (text.length() < width) {
        int spaces = width - text.length();
        for (int i: ranges::views::iota(0, spaces)) {
            text = " " + text;
        }
    }
    return text;
}

string Day7::Part1() {
    cout << endl;
    auto lines = Helpers::readFile(7, 1);

    vector<Plan> plans{};

    for (std::string &line: lines) {
        Plan temp{line};
        plans.push_back(temp);
    }

    int power{10};
    int rounds{10};

    cout << "   ";

    for (int i: ranges::views::iota(0, rounds + 1)) {
        cout << leftPad(i, 2) << " ";
    }

    cout << endl;

    for (Plan &plan: plans) {
        cout << plan.label << ": " << power << " ";
        int total{0};
        for (int i: ranges::views::iota(0, rounds)) {
            switch (plan.next()) {
                case '+':
                    power++;
                    break;
                case '-':
                    power--;
                    break;
                default:
                    break;
            }

            cout << leftPad(power, 2) << " ";
            total += power;
        }
        cout << "= " << leftPad(total, 4) << endl;
        plan.total = total;
        power = 10;
    }

    sort(plans.begin(), plans.end());

    string order;

    for (Plan &plan: plans) {
        order += plan.label;
    }

    return order;
}
