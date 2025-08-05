#pragma once
#include <memory>
#include <spdlog/spdlog.h>

/**
 * @brief Wrapper around spdlog for structured logging.
 */
class Logger {
public:
    static void init();
    static std::shared_ptr<spdlog::logger>& instance();
};

