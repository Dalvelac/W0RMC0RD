#include "TokenLoader.hpp"
#include <fstream>
#include <regex>
#include <stdexcept>

TokenLoader::TokenLoader(const std::string& filePath) : path_(filePath) {}

bool TokenLoader::isValidToken(const std::string& token) const {
    static const std::regex pattern("^[A-Za-z0-9_\\.-]{10,}$");
    return std::regex_match(token, pattern);
}

std::vector<std::string> TokenLoader::load() const {
    std::ifstream file(path_);
    if (!file) {
        throw std::runtime_error("Unable to open token file: " + path_);
    }
    std::vector<std::string> tokens;
    std::string line;
    while (std::getline(file, line)) {
        if (isValidToken(line)) {
            tokens.push_back(line);
        }
    }
    return tokens;
}

