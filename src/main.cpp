#include "TokenLoader.hpp"
#include "WormLogic.hpp"
#include "Logger.hpp"
#include "RateLimiter.hpp"
#include "KillSwitch.hpp"
#include <iostream>

int main() {
    Logger::init();
    try {
        TokenLoader loader("tokens.txt");
        auto tokens = loader.load();
        if (tokens.empty()) {
            Logger::instance()->warn("No valid tokens found.");
            return 0;
        }

        RateLimiter limiter(5); // 5 operations per second
        KillSwitch killSwitch("killswitch");
        killSwitch.start();

        WormLogic worm(std::move(tokens), "http://localhost:5000", limiter, killSwitch);
        worm.run();

        killSwitch.stop();
    } catch (const std::exception& ex) {
        Logger::instance()->error("Exception: {}", ex.what());
        return 1;
    }
    return 0;
}

