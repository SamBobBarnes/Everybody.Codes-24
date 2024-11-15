//
// Created by sb17057 on 11/15/2024.
//

#include <map>

#include "Day6.h"
#include "Node.h"
#include "../Helpers.h"

vector<string> findLine(vector<string> *lines, const string &key) {
    for (auto line: &lines) {
        if (key == Helpers::split(line, ':')[0]) return Helpers::split(Helpers::split(line, ':')[1], ',');
    }
    return {};
}

void Day6::NewNode(Node *root, vector<string> *lines) {
    vector<string> q = findLine(lines, root->label);
    for (const string &childLabel: q) {
        Node *child = root->AddTail(childLabel);
        NewNode(child, lines);
    }
}

string Day6::Part1() {
    auto lines = Helpers::readFile(6, 1);
    Node root{"RR"};
    NewNode(&root, &lines);

    PrintNode(&root);


    // map<int, int> counts{};
    // for (auto &apple: apples) {
    //     if (counts[apple->depth]) counts[apple->depth]++;
    //     else counts.insert({apple->depth, 1});
    // }
    //
    // auto unique = counts.find(1)->first;
    //
    // Node *bestApple;
    //
    // for (auto &apple: apples) {
    //     if (apple->depth == unique) bestApple = apple;
    // }

    string pathToApple;
    // bool done{false};
    // Node *current = bestApple;
    //
    // do {
    //     pathToApple = current->label + pathToApple;
    //     if (current->label == "RR") {
    //         done = true;
    //     } else {
    //         current = current->head;
    //     }
    // } while (!done);


    return pathToApple;
}
