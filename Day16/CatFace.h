//
// Created by sb17057 on 11/26/2024.
//

#ifndef CATFACE_H
#define CATFACE_H
#include <map>
#include <string>

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

#endif //CATFACE_H
