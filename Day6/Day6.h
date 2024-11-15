//
// Created by sb17057 on 11/15/2024.
//

#ifndef DAY6_H
#define DAY6_H
#include <iostream>
#include <vector>
#include <map>

#include "Node.h"
using namespace std;

class Day6 {
public:
    static string Part1();

    static int Part2();

    static int Part3();

    static void PrintNode(const Node *root, int depth = 0);

    static void SetDepth(Node *root, int depth = 0);

    static void NewNode(Node *root, vector<string> *lines);
};

inline void Day6::PrintNode(const Node *root, const int depth) {
    string depthString;
    for (int i = 0; i < depth; i++) depthString += " ";
    if (root->apple) {
        cout << depthString << "\033[31m" << "@" << "\033[0m" << endl;
    } else {
        cout << depthString << root->label << ":[ " << endl;
        for (auto &child: root->tails) {
            PrintNode(child, depth + 1);
        }
        cout << depthString << "]" << endl;
    }
}

inline void Day6::SetDepth(Node *root, const int depth) {
    root->depth = depth;
    if (!root->apple) {
        for (const auto child: root->tails) {
            PrintNode(child, depth + 1);
        }
    }
}
#endif //DAY6_H
