#include "Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

static std::shared_ptr<spdlog::logger> logger;

void Logger::init() {
    if (!logger) {
        logger = spdlog::stdout_color_mt("worm");
        logger->set_pattern("%Y-%m-%d %H:%M:%S %^%l%$ %v");
    }
}

std::shared_ptr<spdlog::logger>& Logger::instance() {
    return logger;
}

