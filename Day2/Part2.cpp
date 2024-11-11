//
// Created by Samuel Barnes on 11/11/24.
//


#include <iostream>
#include <vector>
#include <cmath>

#include "Day2.h"
#define alert "\033[31;4m"
#define info "\033[34m"
#define underline "\003[4m"
#define reset "\033[0m"

int Day2::Part2() {
    // std::cout << std::endl;

    const std::string filePath{"Day2/Part2.txt"};
    std::vector<std::string> initialWords{
        "RLZ", "HRHZ", "G", "CT", "DCC", "OW", "LXLQ", "QXS", "ENS", "MGUU", "VUL", "U", "IQSZTWLQLJ", "SRJITALTAM",
        "DR", "CC", "NBLR", "WXVAPEAUJM", "TGSSQZPJNI", "E", "Y", "YEG", "CPJ", "MJ", "XW", "PITF", "UYUCEJBSRS",
        "DSSG", "WOW", "OO", "WP", "UOB", "GT", "A", "DPDVINCYYQ", "JW", "SXLE", "KJWV", "PKNW", "ZMNJHSVPWW", "RBY",
        "IFQF", "AXHIDHBYEW", "SM", "ECWJZXYPLY", "EOB", "QF", "VAGCFZRJUK"
    };
    // std::vector<std::string> initialWords{
    //     "GEL", "ELE"
    // };
    std::vector<std::string> words{};
    for (const auto &word: initialWords) {
        words.push_back(word);
        if (word.length() > 1) {
            std::string reverseWord = reverse(word);
            if (word != reverseWord) words.push_back(reverseWord);
        }
    }
    std::vector<std::string> lines = Helpers::readFile(filePath);
    // std::vector<std::string> lines = {"GELELEN"};


    int total = 0;

    for (const auto &line: lines) {
        std::vector<std::string> tokens = split(line);
        for (const auto &token: tokens) {
            long symbols{0};
            for (const auto &word: words) {
                bool finished{false};

                int subtotal{0};
                int pos{0};
                std::string printLine;
                while (!finished) {
                    int index = token.find(word, pos);
                    if (index == -1) {
                        finished = true;
                        break;
                    }
                    for (int i = 0; i < word.length(); i++) {
                        symbols |= static_cast<long>(pow(2, index + i));
                    }
                    printLine += token.substr(0, index) + alert + word + reset + token.substr(index + word.length());
                    pos = index + 1;
                    subtotal++;
                    // std::cout << printLine << std::endl;
                    printLine = "";
                }
                if (subtotal > 0) {
                    // std::cout << info << word << reset << " " << std::to_string(subtotal) << std::endl;
                }
            }
            int tokenLength = token.length();
            std::string symbolText = reverse(std::bitset<60>(symbols).to_string()).substr(0, tokenLength);
            std::string symbolTextColored;
            int tokenTotal{0};
            for (int i = 0; i < symbolText.length(); i++) {
                if (symbolText[i] == '1') {
                    symbolTextColored += alert;
                    symbolTextColored += "1";
                    symbolTextColored += reset;
                    tokenTotal++;
                } else {
                    symbolTextColored += "0";
                }
            }
            total += tokenTotal;
            // std::cout << symbolTextColored << " : " << info << tokenTotal << reset << std::endl;
        }
        // std::cout << std::endl;
    }

    return total;
}
