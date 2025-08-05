#pragma once
#include <atomic>
#include <string>
#include <thread>

/**
 * @brief Watches for a file to appear and signals termination.
 */
class KillSwitch {
public:
    explicit KillSwitch(const std::string& path);
    ~KillSwitch();

    void start();
    void stop();
    bool triggered() const { return triggered_; }

private:
    void watch();
    std::string path_;
    std::atomic<bool> running_{false};
    std::atomic<bool> triggered_{false};
    std::thread worker_;
};

