//
// Created by Samuel Barnes on 11/11/24.
//


#include <iostream>
#include <vector>
#include "../Helpers.h"

#include "Day2.h"
#define alert "\033[31;4m"
#define underline "\003[4m"
#define reset "\033[0m"

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
                bool finished{false};

                std::string temp = token;

                int subtotal{0};
                std::string printLine = "";
                while (!finished) {
                    int index = temp.find(word);
                    if (index == -1) {
                        finished = true;
                        printLine += temp;
                        break;
                    }
                    std::string prefix = temp.substr(0, index);
                    printLine += prefix;
                    printLine += alert + word + reset;
                    if (!temp.empty()) subtotal++;
                    temp = temp.substr(index + word.length());
                }
                total += subtotal;
                if (subtotal > 0 && word.length() > 2) {
                    printLine += " " + word + " " + std::to_string(subtotal);
                    std::cout << printLine << std::endl;
                }
            }
        }
        std::cout << std::endl;
    }

    return total;
}
