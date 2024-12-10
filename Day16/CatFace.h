//
// Created by sb17057 on 11/26/2024.
//

#ifndef CATFACE_H
#define CATFACE_H
#include <map>
#include <ranges>
#include <string>
#include <vector>

struct CatFace {
    explicit CatFace(const std::string &face): face(face) {
        for (int i = 0; i < face.length(); ++i) {
            chars[face[i]]++;
        }
        chars2[face[0]]++;
        chars2[face[2]]++;
    }

    std::string face{};

    std::map<char, int> chars{};
    std::map<char, int> chars2{};
};

struct LinkedNode {
    explicit LinkedNode(const std::vector<int> &positions, const std::vector<std::vector<CatFace> > *wheels): positions(
        positions) {
        faces = {};
        for (int i = 0; i < wheels->size(); ++i) {
            faces.push_back((*wheels)[i][positions[i]]);
        }

        value = calculateValue();
    }

    std::vector<int> positions;
    std::vector<CatFace> faces;
    int value;
    LinkedNode *up{nullptr};
    LinkedNode *down{nullptr};
    LinkedNode *next{nullptr};

    [[nodiscard]] bool equals(const std::vector<int> &b) const {
        return positions == b;
    }

    std::vector<int> upPosition(const std::vector<std::vector<CatFace> > *wheels) const {
        return adjustPosition(wheels, true);
    }

    std::vector<int> downPosition(const std::vector<std::vector<CatFace> > *wheels) const {
        return adjustPosition(wheels, false);
    }

private:
    int calculateValue() const {
        std::map<char, int> counts{};

        for (const CatFace &cat: faces) {
            for (auto [fst, snd]: cat.chars2) {
                counts[fst] += snd;
            }
        }

        int score{0};
        for (const auto val: counts | std::views::values) {
            if (val >= 3) {
                score += val - 2;
            }
        }

        return score;
    }

    std::vector<int> adjustPosition(const std::vector<std::vector<CatFace> > *wheels, const bool up) const {
        std::vector<int> result{};
        for (int i = 0; i < positions.size(); ++i) {
            int size = (*wheels)[i].size();
            int absolute = (positions[i] + up ? -1 : 1);
            if (absolute < 0) result.push_back(absolute + size);
            else result.push_back(absolute % size);
        }
        return result;
    }
};

#endif //CATFACE_H
