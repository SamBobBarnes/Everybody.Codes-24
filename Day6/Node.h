//
// Created by sb17057 on 11/15/2024.
//


#ifndef NODE_H
#define NODE_H
#include <string>
#include <vector>

struct Node {
    Node *head;
    std::vector<Node *> tails{};
    bool apple{false};
    std::string label;
    int depth;

    bool operator==(const std::string &b) const {
        return label == b;
    }
};

#endif //NODE_H
