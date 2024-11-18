//
// Created by sb17057 on 11/18/2024.
//

#ifndef PAIR_H
#define PAIR_H

struct Pair {
    explicit Pair(const int left, const int right) {
        this->left = left;
        this->right = right;
    }

    int left;
    int right;

    [[nodiscard]] int total() const {
        return left + right;
    }

    bool operator<(const Pair &other) const {
        return total() < other.total();
    }
};

#endif //PAIR_H
