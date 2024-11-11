//
// Created by Samuel Barnes on 11/10/24.
//

#include <iostream>
#include <string>
#include <vector>

#include "Day2.h"

int Day2::Part1() {
    const std::vector<std::string> words{"LOR", "LL", "SI", "OR", "EN", "ON", "UM"};
    const std::string input{
        "LOREM IPSUM DOLOR SIT AMET, CONSECTETUR ADIPISCING ELIT, SED DO EIUSMOD TEMPOR INCIDIDUNT UT LABORE ET DOLORE MAGNA ALIQUA. UT ENIM AD MINIM VENIAM, QUIS NOSTRUD EXERCITATION ULLAMCO LABORIS NISI UT ALIQUIP EX EA COMMODO CONSEQUAT. DUIS AUTE IRURE DOLOR IN REPREHENDERIT IN VOLUPTATE VELIT ESSE CILLUM DOLORE EU FUGIAT NULLA PARIATUR. EXCEPTEUR SINT OCCAECAT CUPIDATAT NON PROIDENT, SUNT IN CULPA QUI OFFICIA DESERUNT MOLLIT ANIM ID EST LABORUM."
    };

    std::vector<std::string> tokens = split(input);

    int total = 0;

    for (const auto &token: tokens) {
        for (const auto &word: words) {
            if (token.find(word) != -1) {
                std::cout << token << " " << word << std::endl;
                total++;
            }
        }
    }

    return total;
}
