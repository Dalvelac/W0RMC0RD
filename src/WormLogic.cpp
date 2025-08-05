#include "WormLogic.hpp"
#include "Logger.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

WormLogic::WormLogic(std::vector<std::string> tokens,
                     const std::string& baseUrl,
                     RateLimiter& limiter,
                     KillSwitch& killSwitch)
    : tokens_(std::move(tokens)), baseUrl_(baseUrl), limiter_(limiter), killSwitch_(killSwitch) {}

void WormLogic::run() {
    for (const auto& token : tokens_) {
        if (killSwitch_.triggered()) {
            Logger::instance()->info("Kill switch triggered. Stopping.");
            break;
        }
        processToken(token);
    }
}

void WormLogic::processToken(const std::string& token) {
    Logger::instance()->info("Processing token: {}", token);

    limiter_.acquire();
    auto loginResp = cpr::Post(cpr::Url{baseUrl_ + "/login"},
                               cpr::Body{json{{"token", token}}.dump()},
                               cpr::Header{{"Content-Type", "application/json"}});
    Logger::instance()->info("Login status: {}", loginResp.status_code);

    limiter_.acquire();
    auto friendsResp = cpr::Get(cpr::Url{baseUrl_ + "/friends"}, cpr::Parameters{{"token", token}});
    auto friendsJson = json::parse(friendsResp.text, nullptr, false);
    if (!friendsJson.is_object()) {
        Logger::instance()->warn("Invalid friends response");
        return;
    }

    for (const auto& friendId : friendsJson["friends"]) {
        if (killSwitch_.triggered()) {
            Logger::instance()->info("Kill switch triggered during friend loop.");
            break;
        }
        limiter_.acquire();
        json payload{{"to", friendId}, {"message", "Hello from simulator"}};
        cpr::Post(cpr::Url{baseUrl_ + "/dm"},
                  cpr::Body{payload.dump()},
                  cpr::Header{{"Content-Type", "application/json"}});
        Logger::instance()->info("Sent DM to {}", friendId.get<std::string>());
    }
}

