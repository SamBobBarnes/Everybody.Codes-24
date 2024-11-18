//
// Created by Samuel Barnes on 11/16/24.
//

#include <algorithm>
#include <set>

#include "Day7.h"
#include "Plan.h"
#include "../Point.h"

int CountChars(string s, char charToKeep) {
    int count{0};
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == charToKeep) count++;
    }
    return count;
}

string TrackMap() {
    vector<string> map{
        "S+= +=-== +=++=     =+=+=--=    =-= ++=     +=-  =+=++=-+==+ =++=-=-=--",
        "- + +   + =   =     =      =   == = - -     - =  =         =-=        -",
        "= + + +-- =-= ==-==-= --++ +  == == = +     - =  =    ==++=    =++=-=++",
        "+ + + =     +         =  + + == == ++ =     = =  ==   =   = =++=       ",
        "= = + + +== +==     =++ == =+=  =  +  +==-=++ =   =++ --= + =          ",
        "+ ==- = + =   = =+= =   =       ++--          +     =   = = =--= ==++==",
        "=     ==- ==+-- = = = ++= +=--      ==+ ==--= +--+=-= ==- ==   =+=    =",
        "-               = = = =   +  +  ==+ = = +   =        ++    =          -",
        "-               = + + =   +  -  = + = = +   =        +     =          -",
        "--==++++==+=+++-= =-= =-+-=  =+-= =-= =--   +=++=+++==     -=+=++==+++-"
    };

    int width = map[0].length();
    int height = map.size();

    Point previous{0, 0};
    Point current{0, 0};
    int direction{1};
    bool done = false;
    string track;

    while (!done) {
        Point next{0, 0};
        switch (direction) {
            case 0: //Up
                next = {current.x, current.y - 1};
                break;
            case 1: //Right
                next = {current.x + 1, current.y};
                break;
            case 2: //Down
                next = {current.x, current.y + 1};
                break;
            case 3: //Left
                next = {current.x - 1, current.y};
                break;
            default:
                cout << "TILT" << endl;
        }
        if (next.y < 0 || next.y == height || next.x < 0 || next.x == width || map[next.y][next.x] == ' ' || (
                next.x == previous.x && next.y == previous.y)) {
            direction++;
            if (direction == 4) direction = 0;
            continue;
        }
        if (map[next.y][next.x] == 'S') done = true;
        track += map[next.y][next.x];
        previous = current;
        current = next;
    }
    return track;
}

string Day7::Part3() {
    auto lines = Helpers::readFile(7, 3);

    string track = TrackMap();
    // cout << endl << "Track: " << track << endl;
    int trackLength = track.length();
    Plan opponentPlan{"opponent", "=-=+=+-++-+"};

    map<char, int> chars{{'=', 3}, {'-', 3}, {'+', 5}};
    int length{11};
    vector<string> allPlans;
    vector<Plan> plans;

    GeneratePlans(&allPlans, chars, length);

    int index{0};
    for (auto &plan: allPlans) {
        if (CountChars(plan, '+') == 5
            && CountChars(plan, '-') == 3
            && CountChars(plan, '=') == 3) {
            plans.emplace_back(to_string(index), plan);
        }
        index++;
    }

    int power{10};
    int laps{11};

    for (Plan &plan: plans) {
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

                total += power;
            }
        }
        plan.total = total;
        power = 10;
    }


    int total{0};
    for (int l: ranges::views::iota(0, laps)) {
        for (int i: ranges::views::iota(0, trackLength)) {
            char trackBoost = track[i];
            char planStep = opponentPlan.next();

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

            total += power;
        }
    }
    opponentPlan.total = total;

    sort(plans.begin(), plans.end());

    int count{0};

    for (Plan &plan: plans) {
        if (plan.total > opponentPlan.total)count++;
    }


    return to_string(count);
}
