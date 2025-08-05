#include <catch2/catch_test_macros.hpp>
#include "WormLogic.hpp"
#include "RateLimiter.hpp"
#include "KillSwitch.hpp"

TEST_CASE("WormLogic handles empty token list", "[WormLogic]") {
    std::vector<std::string> tokens;
    RateLimiter limiter(1);
    KillSwitch ks("ks_test");
    WormLogic worm(tokens, "http://localhost:5000", limiter, ks);
    worm.run();
    REQUIRE(true); // should not crash
}

