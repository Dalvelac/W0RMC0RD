#include "RateLimiter.hpp"
#include <thread>

RateLimiter::RateLimiter(std::size_t opsPerSecond)
    : next_(std::chrono::steady_clock::now()),
      interval_(opsPerSecond ? std::chrono::milliseconds(1000 / opsPerSecond)
                             : std::chrono::milliseconds(1000)) {}

void RateLimiter::acquire() {
    std::unique_lock<std::mutex> lock(mutex_);
    auto now = std::chrono::steady_clock::now();
    if (now < next_) {
        std::this_thread::sleep_for(next_ - now);
    }
    next_ = std::chrono::steady_clock::now() + interval_;
}

