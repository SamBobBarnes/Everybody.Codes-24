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
    }

    std::string face{};

    std::map<char, int> chars{};
};

#endif //CATFACE_H
