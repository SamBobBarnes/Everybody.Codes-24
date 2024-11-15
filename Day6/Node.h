//
// Created by sb17057 on 11/15/2024.
//


#ifndef NODE_H
#define NODE_H
#include <string>
#include <utility>
#include <vector>

struct Node {
    explicit Node(std::string label) {
        this->label = std::move(label);
    }

    explicit Node(std::string label, Node *head, const int depth) {
        this->label = std::move(label);
        this->head = head;
        this->depth = depth;
        if (label == "@") apple = true;
    }

    Node *head{};
    std::vector<Node *> tails{};
    bool apple{false};
    std::string label;
    int depth{};

    bool operator==(const std::string &b) const {
        return label == b;
    }

    Node *AddTail(const std::string &label) {
        tails.emplace_back(label, this, depth + 1);
        return tails.back();
    }
};

#endif //NODE_H
