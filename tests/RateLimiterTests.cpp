#include <catch2/catch_test_macros.hpp>
#include "RateLimiter.hpp"
#include <chrono>

TEST_CASE("RateLimiter enforces delay", "[RateLimiter]") {
    RateLimiter limiter(2); // 2 ops per sec
    auto start = std::chrono::steady_clock::now();
    limiter.acquire();
    limiter.acquire();
    limiter.acquire();
    auto dur = std::chrono::steady_clock::now() - start;
    REQUIRE(dur >= std::chrono::milliseconds(1000));
}

