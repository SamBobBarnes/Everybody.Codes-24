//
// Created by Samuel Barnes on 11/11/24.
//


#include <iostream>
#include <vector>
#include "../Helpers.h"

#include "Day2.h"

int Day2::Part2() {
    const std::string filePath{"Day2/input.txt"};
    std::vector<std::string> initialWords{
        "RLZ", "HRHZ", "G", "CT", "DCC", "OW", "LXLQ", "QXS", "ENS", "MGUU", "VUL", "U", "IQSZTWLQLJ", "SRJITALTAM",
        "DR", "CC", "NBLR", "WXVAPEAUJM", "TGSSQZPJNI", "E", "Y", "YEG", "CPJ", "MJ", "XW", "PITF", "UYUCEJBSRS",
        "DSSG", "WOW", "OO", "WP", "UOB", "GT", "A", "DPDVINCYYQ", "JW", "SXLE", "KJWV", "PKNW", "ZMNJHSVPWW", "RBY",
        "IFQF", "AXHIDHBYEW", "SM", "ECWJZXYPLY", "EOB", "QF", "VAGCFZRJUK"
    };
    std::vector<std::string> words{};
    for (const auto &word: initialWords) {
        words.push_back(word);
        if (word.length() > 1) {
            std::string reverse{""};
            for (int i = word.length() - 1; i >= 0; i--) {
                reverse.push_back(word[i]);
            }
            words.push_back(reverse);
        }
    }
    std::vector<std::string> lines = Helpers::readFile(filePath);


    int total = 0;

    for (const auto &line: lines) {
        std::vector<std::string> tokens = split(line);
        for (const auto &token: tokens) {
            for (const auto &word: words) {
                if (token.find(word) != -1) {
                    std::cout << token << " " << word << std::endl;
                    total++;
                }
            }
        }
    }

    return total;
}
