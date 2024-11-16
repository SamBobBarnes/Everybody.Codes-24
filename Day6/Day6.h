//
// Created by sb17057 on 11/15/2024.
//

#ifndef DAY6_H
#define DAY6_H
#include <iostream>
#include <vector>
#include <map>

#include "Node.h"
#include "../Helpers.h"
using namespace std;

class Day6 {
public:
    static string Part1();

    static string Part2();

    static string Part3();

    static void PrintNode(Node *root, int depth = 0);

    static void NewNode(Node *root, const vector<string> &lines);

    static void FindApples(Node *root, vector<string> *paths, const string &currentPath);

private:
    static vector<string> findLine(const vector<string> &lines, const string &key) {
        for (const auto &line: lines) {
            if (key == Helpers::split(line, ':')[0]) return Helpers::split(Helpers::split(line, ':')[1], ',');
        }
        return {};
    }
};

inline void Day6::FindApples(Node *root, vector<string> *paths, const string &currentPath) {
    if (root->apple) paths->push_back(currentPath);
    for (auto &child: root->tails) {
        FindApples(&child, paths, currentPath + child.label.substr(0, 1));
    }
}


inline void Day6::PrintNode(Node *root, const int depth) {
    string depthString;
    for (int i = 0; i < depth; i++) depthString += " ";
    if (root->apple) {
        cout << depthString << "\033[31m" << "@" << "\033[0m" << endl;
    } else {
        cout << depthString << root->label << ":[ " << endl;
        for (auto &child: root->tails) {
            PrintNode(&child, depth + 1);
        }
        cout << depthString << "]" << endl;
    }
}

inline void Day6::NewNode(Node *root, const vector<string> &lines) {
    vector<string> q = findLine(lines, root->label);
    for (const string &childLabel: q) {
        Node *child = root->AddTail(childLabel);
        NewNode(child, lines);
    }
}
#endif //DAY6_H
