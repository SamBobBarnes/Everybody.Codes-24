//
// Created by Samuel Barnes on 11/11/24.
//

#include <fstream>
#include <iostream>
#include <vector>

#include "Day2.h"

int Day2::Part2() {
    std::vector<std::string> words{
        "RLZ", "HRHZ", "G", "CT", "DCC", "OW", "LXLQ", "QXS", "ENS", "MGUU", "VUL", "U", "IQSZTWLQLJ", "SRJITALTAM",
        "DR", "CC", "NBLR", "WXVAPEAUJM", "TGSSQZPJNI", "E", "Y", "YEG", "CPJ", "MJ", "XW", "PITF", "UYUCEJBSRS",
        "DSSG", "WOW", "OO", "WP", "UOB", "GT", "A", "DPDVINCYYQ", "JW", "SXLE", "KJWV", "PKNW", "ZMNJHSVPWW", "RBY",
        "IFQF", "AXHIDHBYEW", "SM", "ECWJZXYPLY", "EOB", "QF", "VAGCFZRJUK"
    };

    for (const auto &word: words) {
        std::string reverse{""};
        for (int i = word.length(); i >= 0; i--) {
            reverse.push_back(word[i]);
        }
        words.push_back(reverse);
    }
    std::vector<std::vector<std::string> > tokenList{};

    std::cout << system("pwd") << std::endl;
    std::ifstream inputFile("../Day2/input.txt");
    std::string line;
    long count = inputFile.gcount();


    int total = 0;
}
