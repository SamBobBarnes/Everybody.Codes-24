//
// Created by sb17057 on 11/15/2024.
//

#include <map>

#include "Day6.h"
#include "Node.h"
#include "../Helpers.h"

string Day6::Part1() {
    auto lines = Helpers::readFile(6, 1);
    vector<Node> nodes{};
    vector<Node> apples{};

    for (auto &line: lines) {
        Node node{};
        node.label = Helpers::split(line, ':')[0];
        nodes.push_back(node);
    }

    for (auto &line: lines) {
        const auto childrenLabels = Helpers::split(Helpers::split(line, ':')[1], ',');
        for (auto &childLabel: childrenLabels) {
            if (childLabel == "@") continue;
            auto childIterator = find(nodes.begin(), nodes.end(), childLabel);
            if (childIterator == nodes.end()) {
                Node newChild{};
                newChild.label = childLabel;
                nodes.push_back(newChild);
            }
        }
    }

    for (auto &line: lines) {
        const auto nodeLabel = Helpers::split(line, ':')[0];
        auto *node = &*find(nodes.begin(), nodes.end(), nodeLabel);
        const auto childrenLabels = Helpers::split(Helpers::split(line, ':')[1], ',');
        for (auto &childLabel: childrenLabels) {
            if (childLabel == "@") {
                Node apple{};
                apple.label = "@";
                apple.apple = true;
                apple.head = node;
                apples.push_back(apple);
                Node *savedApple = &apples[apples.size()-1];
                node->tails.push_back(savedApple);
            } else {
                Node *child = &*find(nodes.begin(), nodes.end(), childLabel);
                child->head = node;
                node->tails.push_back(child);
            }
        }
    }

    cout << endl;
    Node *root = &*find(nodes.begin(), nodes.end(), "RR");
    root->depth = 0;
    SetDepth(root);
    PrintNode(root);


    map<int, int> counts{};
    for (auto &apple: apples) {
        if (counts[apple.depth]) counts[apple.depth]++;
        else counts.insert({apple.depth, 1});
    }

    auto unique = counts.find(1)->first;

    Node *bestApple;

    for (auto &apple: apples) {
        if (apple.depth == unique) bestApple = &apple;
    }

    string pathToApple;
    bool done{false};
    Node *current = bestApple;

    do {
        pathToApple = current->label + pathToApple;
        if (current->label == "RR") {
            done = true;
        } else {
            current = current->head;
        }
    } while (!done);


    return pathToApple;
}
