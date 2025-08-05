#pragma once
#include <string>
#include <vector>
#include "RateLimiter.hpp"
#include "KillSwitch.hpp"

/**
 * @brief Simulates basic worm actions against a stubbed Discord API.
 */
class WormLogic {
public:
    WormLogic(std::vector<std::string> tokens,
              const std::string& baseUrl,
              RateLimiter& limiter,
              KillSwitch& killSwitch);

    /**
     * @brief Run the worm simulation for all tokens.
     */
    void run();

private:
    void processToken(const std::string& token);

    std::vector<std::string> tokens_;
    std::string baseUrl_;
    RateLimiter& limiter_;
    KillSwitch& killSwitch_;
};

