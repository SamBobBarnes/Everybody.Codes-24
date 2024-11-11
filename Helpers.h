//
// Created by Samuel Barnes on 11/11/24.
//

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <cerrno>
#include <iostream>
#include <vector>

#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <fstream>


class Helpers {
public:
    static std::string pwd() {
        char cCurrentPath[FILENAME_MAX];

        if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
            std::cout << errno << std::endl;
            throw std::runtime_error("Invalid path length");
        }

        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */

        return cCurrentPath;
    }

    static std::vector<std::string> readFile(const std::string &path, bool debug = false) {
        std::vector<std::string> lines{};
        std::string filePath = pwd() + "/../" + path;
        if (debug) std::cout << "Reading file from " << filePath << std::endl;
        std::ifstream inputFile(filePath);
        std::string line;
        if (inputFile.is_open()) {
            while (getline(inputFile, line)) {
                lines.push_back(line);
            }
            inputFile.close();
        } else std::cout << "Unable to open file";

        return lines;
    }
};


#endif //HELPERS_H
