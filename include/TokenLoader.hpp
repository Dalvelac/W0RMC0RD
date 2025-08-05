#pragma once
#include <string>
#include <vector>

/**
 * @brief Loads Discord tokens from a file and validates their format.
 */
class TokenLoader {
public:
    /**
     * @param filePath Path to the token file.
     */
    explicit TokenLoader(const std::string& filePath);

    /**
     * @brief Load and validate tokens.
     * @return Vector of valid tokens.
     * @throws std::runtime_error if file cannot be read.
     */
    std::vector<std::string> load() const;

private:
    bool isValidToken(const std::string& token) const;
    std::string path_;
};

