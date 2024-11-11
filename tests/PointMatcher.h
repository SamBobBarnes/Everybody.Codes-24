//
// Created by sb17057 on 11/11/2024.
//
#pragma once

#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>
#include "../Day2/FindResult.h"

#ifndef POINTMATCHER_H
#define POINTMATCHER_H

struct Point;

class PointMatcher : public Catch::Matchers::MatcherGenericBase {
public:
    explicit PointMatcher(const Point &expected) : m_expected(expected) {
    }

    bool match(const Point &actual) const {
        return actual == m_expected;
    }

    std::string describe() const override {
        std::ostringstream ss;
        ss << "is equal to {" << m_expected.x << ", " << m_expected.y << "}";
        return ss.str();
    }

private:
    Point m_expected;
};

bool compareVectors(const std::vector<Point> &vec1, const std::vector<Point> &vec2) {
    if (vec1.size() != vec2.size()) return false;
    for (size_t i = 0; i < vec1.size(); ++i) {
        if (!(vec1[i] == vec2[i])) return false;
    }
    return true;
}

#endif //POINTMATCHER_H
