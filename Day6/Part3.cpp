//
// Created by sb17057 on 11/15/2024.
//

#include <map>

#include "Day6.h"
#include "../Helpers.h"

string Day6::Part3() {
    auto lines = Helpers::readFile(6, 3);
    Node root{"RR"};
    NewNode(&root, lines);

    // PrintNode(&root);

    string pathToApple;
    vector<string> pathsToApples;
    map<int, vector<string *> > pathLengths;

    FindApples(&root, &pathsToApples, "R");

    for (string &path: pathsToApples) {
        int length = path.length();
        if (pathLengths.contains(length)) pathLengths[length].push_back(&path);
        else pathLengths.insert({length, {&path}});
    }

    for (auto &length: pathLengths) {
        if (length.second.size() == 1) pathToApple = *length.second.front();
    }

    return pathToApple;
}
