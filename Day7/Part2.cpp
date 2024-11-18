//
// Created by Samuel Barnes on 11/16/24.
//

#include <algorithm>

#include "Day7.h"
#include "Plan.h"

string Day7::Part2() {
    const string track{
        "-=++=-==++=++=-=+=-=+=+=--=-=++=-==++=-+=-=+=-=+=+=++=-+==++=++=-=-=---=++==--+++==++=+=--==++==+++=++=+++=--=+=-=+=-+=-+=-+-=+=-=+=-+++=+==++++==---=+=+=-S"
    };
    auto lines = Helpers::readFile(7, 2);

    int trackLength = track.length();
    // cout << endl;

    vector<Plan> plans{};

    for (std::string &line: lines) {
        Plan temp{line};
        plans.push_back(temp);
    }

    int power{10};
    int laps{10};

    // cout << "     ";

    // for (int l: ranges::views::iota(0, laps)) {
    //     for (int i: ranges::views::iota(0, trackLength)) {
    //         if (trackLength - 1 == i) {
    //             cout << "  S ";
    //         } else cout << "  " << track[i] << " ";
    //     }
    // }

    // cout << endl;

    for (Plan &plan: plans) {
        // cout << plan.label << ": " << power << " ";
        int total{0};
        for (int l: ranges::views::iota(0, laps)) {
            for (int i: ranges::views::iota(0, trackLength)) {
                char trackBoost = track[i];
                char planStep = plan.next();

                switch (trackBoost) {
                    case '+':
                        power++;
                        break;
                    case '-':
                        power--;
                        break;
                    case '=':
                    case 'S':
                        switch (planStep) {
                            case '+':
                                power++;
                                break;
                            case '-':
                                power--;
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        cout << "TILT" << endl;
                }

                // cout << Helpers::leftPad(power, 3) << " ";
                total += power;
            }
        }
        // cout << "= " << Helpers::leftPad(total, 4) << endl;
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
