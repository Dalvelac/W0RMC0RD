#pragma once
#include <chrono>
#include <mutex>

/**
 * @brief Simple rate limiter based on a fixed interval.
 */
class RateLimiter {
public:
    /**
     * @param opsPerSecond Allowed operations per second. Must be >0.
     */
    explicit RateLimiter(std::size_t opsPerSecond);

    /**
     * @brief Acquire permission for the next operation.
     */
    void acquire();

private:
    std::chrono::steady_clock::time_point next_;
    std::chrono::milliseconds interval_;
    std::mutex mutex_;
};

